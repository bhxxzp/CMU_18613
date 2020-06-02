/**
 * @file mm.c
 * @brief A 64-bit struct-based implicit free list memory allocator
 *
 * 15-213: Introduction to Computer Systems
 *
 * For this lab, I use FIFO to find the suitable block in free list.
 * What I use to improve the throughput is segregated list. To find the
 * suitable block, the algorithsm looks like the hashcode in JAVA.
 *
 *************************************************************************
 *
 * ADVICE FOR STUDENTS.
 * - Step 0: Please read the writeup!
 * - Step 1: Write your heap checker.
 * - Step 2: Write contracts / debugging assert statements.
 * - Good luck, and have fun!
 *
 *************************************************************************
 *
 * @author Peng Zeng
 * @andrewID pengzeng
 */

#include <assert.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "memlib.h"
#include "mm.h"

/* Do not change the following! */

#ifdef DRIVER
/* create aliases for driver tests */
#define malloc mm_malloc
#define free mm_free
#define realloc mm_realloc
#define calloc mm_calloc
#define memset mem_memset
#define memcpy mem_memcpy
#endif /* def DRIVER */

/* You can change anything from here onward */

/*
 *****************************************************************************
 * If DEBUG is defined (such as when running mdriver-dbg), these macros      *
 * are enabled. You can use them to print debugging output and to check      *
 * contracts only in debug mode.                                             *
 *                                                                           *
 * Only debugging macros with names beginning "dbg_" are allowed.            *
 * You may not define any other macros having arguments.                     *
 *****************************************************************************
 */
#ifdef DEBUG
/* When DEBUG is defined, these form aliases to useful functions */
#define dbg_printf(...) printf(__VA_ARGS__)
#define dbg_requires(expr) assert(expr)
#define dbg_assert(expr) assert(expr)
#define dbg_ensures(expr) assert(expr)
#define dbg_printheap(...) print_heap(__VA_ARGS__)
#else
/* When DEBUG is not defined, no code gets generated for these */
/* The sizeof() hack is used to avoid "unused variable" warnings */
#define dbg_printf(...) (sizeof(__VA_ARGS__), -1)
#define dbg_requires(expr) (sizeof(expr), 1)
#define dbg_assert(expr) (sizeof(expr), 1)
#define dbg_ensures(expr) (sizeof(expr), 1)
#define dbg_printheap(...) ((void)sizeof(__VA_ARGS__))
#endif

/* Basic constants */

typedef uint64_t word_t;

/** @brief Word and header size (8 bytes) */
static const size_t wsize = sizeof(word_t);

/** @brief Double word size (16 bytes) */
static const size_t dsize = 2 * wsize;

/** @brief Minimum block size (32 bytes) */
static const size_t min_block_size = 2 * dsize;

/**
 * The size of the free block we assign at first time
 * or the default block size to expend
 * (Must be divisible by dsize)
 */
static const size_t chunksize = (1 << 12);

/**
 * alloc_mask to get the last alloc bit
 */
static const word_t alloc_mask = 0x1;

/**
 * alloc_mask to get the prev alloc bit
 */
static const word_t prev_alloc_mask = 0x2;

/**
 * size_mask to get the size bits of the block
 */
static const word_t size_mask = ~(word_t)0xF;

/**
 * 128 Bytes - 8 Bytes(Header) = 120
 * 120 / 8 = 15 Bytes
 * Should smaller than 15
 */
static const size_t list_number = 12;

/**
 * Initialize the range of the list
 */
static const size_t list_index = 1;

/** @brief Represents the header and payload of one block in the heap */
typedef struct block {
    /** @brief Header contains size + allocation flag */
    word_t header;
    union {
        struct {
            struct block *prev;
            struct block *next;
        } free_block;
        char payload[0];
    } info;
} block_t;

/* Global variables */
static block_t *seg_list[list_number]; // the list of all the segregate lists

/** @brief Pointer to first block in the heap */
static block_t *heap_start = NULL;

/*
 *****************************************************************************
 * The functions below are short wrapper functions to perform                *
 * bit manipulation, pointer arithmetic, and other helper operations.        *
 *                                                                           *
 * We've given you the function header comments for the functions below      *
 * to help you understand how this baseline code works.                      *
 *                                                                           *
 * Note that these function header comments are short since the functions    *
 * they are describing are short as well; you will need to provide           *
 * adequate details within your header comments for the functions above!     *
 *****************************************************************************
 */

/*
 * ---------------------------------------------------------------------------
 *                        BEGIN SHORT HELPER FUNCTIONS
 * ---------------------------------------------------------------------------
 */

static block_t *find_prev(block_t *block);
static block_t *find_next(block_t *block);
static void write_footer(block_t *block, size_t size, bool alloc,
                         bool prev_alloc);
static void write_header(block_t *block, size_t size, bool alloc,
                         bool prev_alloc);
static size_t get_index(size_t asize);
static void delete_block(block_t *block);
static void insert_block(block_t *block);
bool mm_init(void);
/**
 * @brief Returns the maximum of two integers.
 * @param[in] x
 * @param[in] y
 * @return `x` if `x > y`, and `y` otherwise.
 */
static size_t max(size_t x, size_t y) {
    return (x > y) ? x : y;
}

/**
 * @brief Rounds `size` up to next multiple of n
 * @param[in] size
 * @param[in] n
 * @return The size after rounding up
 */
static size_t round_up(size_t size, size_t n) {
    return n * ((size + (n - 1)) / n);
}

/**
 * @brief Packs the `size` and `alloc` of a block into a word suitable for
 *        use as a packed value.
 *
 * Packed values are used for both headers and footers.
 *
 * The allocation status is packed into the lowest bit of the word.
 *
 * @param[in] size The size of the block being represented
 * @param[in] alloc True if the block is allocated
 * @return The packed value
 */
static word_t pack(size_t size, bool alloc, bool prev_alloc) {
    word_t word;
    if (alloc) {
        word = (size | alloc_mask);
    } else {
        word = size;
    }
    if (prev_alloc) {
        word = (word | prev_alloc_mask);
    }
    return word;
}

/**
 * @brief Extracts the size represented in a packed word.
 *
 * This function simply clears the lowest 4 bits of the word, as the heap
 * is 16-byte aligned.
 *
 * @param[in] word
 * @return The size of the block represented by the word
 */
static size_t extract_size(word_t word) {
    return (word & size_mask);
}

/**
 * @brief Extracts the size of a block from its header.
 * @param[in] block
 * @return The size of the block
 */
static size_t get_size(block_t *block) {
    return extract_size(block->header);
}

/**
 * @brief Given a payload pointer, returns a pointer to the corresponding
 *        block.
 * @param[in] bp A pointer to a block's payload
 * @return The corresponding block
 */
static block_t *payload_to_header(void *bp) {
    return (block_t *)((char *)bp - offsetof(block_t, info.payload));
}

/**
 * @brief Given a block pointer, returns a pointer to the corresponding
 *        payload.
 * @param[in] block
 * @return A pointer to the block's payload
 */
static void *header_to_payload(block_t *block) {
    return (void *)(block->info.payload);
}

/**
 * @brief Given a block pointer, returns a pointer to the corresponding
 *        footer.
 * @param[in] block
 * @return A pointer to the block's footer
 */
static word_t *header_to_footer(block_t *block) {
    return (word_t *)(block->info.payload + get_size(block) - dsize);
}

/**
 * @brief Given a block footer, returns a pointer to the corresponding
 *        header.
 * @param[in] footer A pointer to the block's footer
 * @return A pointer to the start of the block
 */
static block_t *footer_to_header(word_t *footer) {
    size_t size = extract_size(*footer);
    return (block_t *)((char *)footer + wsize - size);
}

/**
 * @brief Returns the payload size of a given block.
 *
 * The payload size is equal to the entire block size minus the sizes of the
 * block's header and footer.
 *
 * @param[in] block
 * @return The size of the block's payload
 */
static size_t get_payload_size(block_t *block) {
    size_t asize = get_size(block);
    return asize - dsize;
}

/**
 * @brief Returns the allocation status of a given header value.
 *
 * This is based on the lowest bit of the header value.
 *
 * @param[in] word
 * @return The allocation status correpsonding to the word
 */
static bool extract_alloc(word_t word) {
    return (bool)(word & alloc_mask);
}

static bool extract_prev_alloc(word_t word) {
    return (bool)(word & prev_alloc_mask);
}

/**
 * @brief Returns the allocation status of a block, based on its header.
 * @param[in] block
 * @return The allocation status of the block
 */
static bool get_alloc(block_t *block) {
    return extract_alloc(block->header);
}

/**
 * @brief Returns the allocation status of the previous block, based on its
 * header.
 * @param[in] block
 * @return The allocation status of the block
 */
static bool get_prev_alloc(block_t *block) {
    return extract_prev_alloc(block->header);
}

/**
 * @brief Returns the allocation status of the next block, based on its header.
 * @param[in] block
 * @return The allocation status of the block
 */
static bool get_next_alloc(block_t *block) {
    block_t *next_block = find_next(block);
    return extract_alloc(next_block->header);
}

static void set_nextblock_prev_alloc(block_t *block, bool prev_alloc) {
    block_t *next_block = find_next(block);
    size_t next_size = get_size(next_block);
    bool next_alloc = get_alloc(next_block);
    write_header(next_block, next_size, next_alloc, prev_alloc);
}

/**
 * @brief Writes an epilogue header at the given address.
 *
 * The epilogue header has size 0, and is marked as allocated.
 *
 * @param[out] block The location to write the epilogue header
 */
// static void write_epilogue(block_t *block) {
//     dbg_requires(block != NULL);
//     dbg_requires((char *)block == mem_heap_hi() - 7);
//     block->header = pack(0, true);
// }

/**
 * @brief Writes a block starting at the given address.
 *
 * This function writes both a header and footer, where the location of the
 * footer is computed in relation to the header.
 *
 * @param[out] block The location to begin writing the block header
 * @param[in] size The size of the new block
 * @param[in] alloc The allocation status of the new block
 */
// static void write_block(block_t *block, size_t size, bool alloc) {
//     dbg_requires(block != NULL);
//     dbg_requires(size > 0);
//     block->header = pack(size, alloc);
//     word_t *footerp = header_to_footer(block);
//     *footerp = pack(size, alloc);
// }

/**
 * @brief Writes an header at the given address.
 *
 * @param[out] block The location to write the epilogue header
 */
static void write_header(block_t *block, size_t size, bool alloc,
                         bool prev_alloc) {
    dbg_requires(block != NULL);
    block->header = pack(size, alloc, prev_alloc);
}

/**
 * @brief Writes an  footer at the given address.
 *
 * @param[out] block The location to write the epilogue header
 */
static void write_footer(block_t *block, size_t size, bool alloc,
                         bool prev_alloc) {
    dbg_requires(block != NULL);
    dbg_requires(get_size(block) == size && size > 0);
    word_t *footerp = header_to_footer(block);
    *footerp = pack(size, alloc, prev_alloc);
}

/**
 * @brief Finds the next consecutive block on the heap.
 *
 * This function accesses the next block in the "implicit list" of the heap
 * by adding the size of the block.
 *
 * @param[in] block A block in the heap
 * @return The next consecutive block on the heap
 * @pre The block is not the epilogue
 */
static block_t *find_next(block_t *block) {
    dbg_requires(block != NULL);
    dbg_requires(get_size(block) != 0);
    return (block_t *)((char *)block + get_size(block));
}

/**
 * @brief Finds the footer of the previous block on the heap.
 * @param[in] block A block in the heap
 * @return The location of the previous block's footer
 */
static word_t *find_prev_footer(block_t *block) {
    // Compute previous footer position as one word before the header
    return &(block->header) - 1;
}

/**
 * @brief Finds the previous consecutive block on the heap.
 *
 * This is the previous block in the "implicit list" of the heap.
 *
 * The position of the previous block is found by reading the previous
 * block's footer to determine its size, then calculating the start of the
 * previous block based on its size.
 *
 * @param[in] block A block in the heap
 * @return The previous consecutive block in the heap
 * @pre The block is not the first block in the heap
 */
/*
 *
 */
static block_t *find_prev(block_t *block) {
    dbg_requires(block != NULL);
    dbg_requires(get_size(block) != 0);
    word_t *footerp = find_prev_footer(block);
    return footer_to_header(footerp);
}

/*
 * ---------------------------------------------------------------------------
 *                        END SHORT HELPER FUNCTIONS
 * ---------------------------------------------------------------------------
 */

/******** The remaining content below are helper and debug routines ********/

/**
 * @brief
 *
 * @functions: To coalesce the block under different cases
 * @arguments: the block we need to coalesce
 * @preconditions: we only call this function when we are freeing a block
 * @param[in] block
 * @return the block after coalescing
 */
static block_t *coalesce_block(block_t *block) {
    dbg_requires(!get_alloc(block));
    size_t size = get_size(block);
    block_t *next_block = find_next(block);
    bool prev_alloc = get_prev_alloc(block);
    bool next_alloc = get_alloc(next_block);
    // Case 1
    // Previous and next alloc
    if (next_alloc && prev_alloc) {
        set_nextblock_prev_alloc(block, false);
        insert_block(block);
        // set_nextblock_pre_alloc(block, false);
    }
    // Case 2
    // Previous alloc and next not alloc
    // Coalesce next block
    else if (prev_alloc && !next_alloc) {
        size += get_size(next_block);
        delete_block(next_block);
        write_header(block, size, false, true);
        write_footer(block, size, false, true);
        set_nextblock_prev_alloc(block, false);
        insert_block(block);
    }
    // Case 3
    // Previous not alloc and next alloc
    // Coalesce previous block
    else if (!prev_alloc && next_alloc) {
        block_t *prev_block = find_prev(block);
        size += get_size(prev_block);
        delete_block(prev_block);
        write_header(prev_block, size, false, true);
        write_footer(prev_block, size, false, true);
        set_nextblock_prev_alloc(block, false);
        block = prev_block;
        insert_block(block);
    }
    // Case 4
    // Coalesce both previous and next
    else {
        block_t *prev_block = find_prev(block);
        size += get_size(prev_block);
        size += get_size(next_block);
        delete_block(prev_block);
        delete_block(next_block);
        write_header(prev_block, size, false, true);
        write_footer(prev_block, size, false, true);
        set_nextblock_prev_alloc(prev_block, false);
        block = prev_block;
        insert_block(block);
    }
    // insert_block(block);
    dbg_ensures(!get_alloc(block));
    dbg_requires(mm_checkheap(__LINE__));
    return block;
}

/**
 * @brief
 *
 * @functions: extend the heap when the space is limited or when we found the
 * heap
 * @arguments: how many size we need to extend
 * @preconditions: the size we extend should be the multiple of dsize
 * @param[in] size
 * @return the new block after extending
 */
static block_t *extend_heap(size_t size) {
    void *bp;

    // Allocate an even number of words to maintain alignment
    size = round_up(size, dsize);
    if ((bp = mem_sbrk(size)) == (void *)-1) {
        return NULL;
    }

    // Initialize free block header/footer
    block_t *block = payload_to_header(bp);
    bool prev_alloc = get_prev_alloc(block);
    // bool next_alloc = get_next_alloc(block);
    write_header(block, size, false, prev_alloc);
    write_footer(block, size, false, prev_alloc);

    // Create new epilogue header
    block_t *next_block = find_next(block);
    write_header(next_block, 0, true, false);

    // Coalesce in case the previous block was free
    block = coalesce_block(block);
    dbg_requires(mm_checkheap(__LINE__));
    return block;
}

/**
 * @brief
 *
 * @functions: after mallocing the block we need to split the free block
 * @arguments: the block we split and how many sizes it is
 * @return NULL
 * @preconditions: the left space is bigger than or equal to the size we need
 * @param[in] block
 * @param[in] asize
 */
static void split_block(block_t *block, size_t asize) {
    dbg_requires(!get_alloc(block));
    /* TODO: Can you write a precondition about the value of asize? */

    size_t block_size = get_size(block);

    delete_block(block);

    if ((block_size - asize) >= min_block_size) {
        write_header(block, asize, true, true);
        // write_footer(block, asize, true, true);

        block_t *next_block = find_next(block);
        write_header(next_block, block_size - asize, false, true);
        write_footer(next_block, block_size - asize, false, true);

        // block_t *next_next_block = find_next(next_block);
        set_nextblock_prev_alloc(next_block, false);
        insert_block(next_block);
    } else {
        write_header(block, block_size, true, true);
        set_nextblock_prev_alloc(block, true);
    }

    dbg_ensures(get_alloc(block));
}

/**
 * @brief
 *
 * @functions: delete the block in the heap and change the pointer in block
 * @arguments: the block we need to delete
 * @preconditions: NULL
 * @param[in] size
 * @return NULL
 */
static void delete_block(block_t *block) {
    // printf("jinru\n");

    if (block == NULL) {
        // printf("null");
        return;
    }

    size_t asize = round_up(get_size(block), dsize);
    size_t index = get_index(asize);

    // no block in this list
    if (!block->info.free_block.prev && !block->info.free_block.next) {
        // printf("------------------\n");
        // printf("no prev no next\n");
        // printf("block: %p\n", block);
        // printf("index: %zu\n", index);
        // printf("\n");
        seg_list[index] = NULL;
        return;
    }
    // the first block
    else if (!block->info.free_block.prev && !!(block->info.free_block.next)) {
        block_t *next_block = block->info.free_block.next;
        next_block->info.free_block.prev = NULL;
        // printf("------------------\n");
        // printf("no prev yes next\n");
        // printf("block: %p\n", block);
        // printf("next_block: %p\n", next_block);
        // printf("index: %zu\n", index);
        // printf("\n");
        seg_list[index] = next_block;
        return;
    }
    // the last block
    else if (!block->info.free_block.next && !!(block->info.free_block.prev)) {
        block_t *prev_block = block->info.free_block.prev;
        // printf("------------------\n");
        // printf("yes prev no next\n");
        // printf("block: %p\n", block);
        // printf("prev_block: %p\n", prev_block);
        // printf("index: %zu\n", index);
        // printf("\n");
        prev_block->info.free_block.next = NULL;
        return;
    }
    // normal
    else {
        block_t *next_block = block->info.free_block.next;
        block_t *prev_block = block->info.free_block.prev;
        // printf("------------------\n");
        // printf("yes prev yes next\n");
        // printf("block: %p\n", block);
        // printf("prev_block: %p\n", prev_block);
        // printf("next_block: %p\n", next_block);
        // printf("index: %zu\n", index);
        // printf("\n");
        prev_block->info.free_block.next = next_block;
        next_block->info.free_block.prev = prev_block;
        return;
    }
}

/**
 * @brief
 *
 * @functions: insert the free block into segregate list, implementing with LIFO
 * @arguments: the block we need to insert
 * @preconditions: NULL
 * @param[in] size
 * @return NULL
 */
static void insert_block(block_t *block) {
    if (!block) {
        return;
    }
    size_t asize = round_up(get_size(block), dsize);
    size_t index = get_index(asize);
    // if it is the first block in this list
    if (!seg_list[index]) {
        seg_list[index] = block;
        block->info.free_block.next = NULL;
        block->info.free_block.prev = NULL;
        return;
    }
    // LIFO
    else {
        seg_list[index]->info.free_block.prev = block;
        block->info.free_block.next = seg_list[index];
        block->info.free_block.prev = NULL;
        seg_list[index] = block;
        return;
    }
}

/**
 * @brief
 *
 * @functions: to get the index in the segregate list to find which position to
 * store the free block. It looks like the hashcode in JAVA
 * @arguments: the size of the free block
 * @preconditions: segregate list is the global variable
 * @param[in] size
 * @return the index of the position in the segregate list
 * @idea: Get the idea from website:
 *        https://www.cnblogs.com/xiekeli/archive/2012/01/13/2321207.html
 */
static size_t get_index(size_t asize) {
    // if size smaller than double size, return 0
    if (asize < dsize) {
        return 0;

    }
    // if the size larger than the bigger one, return list_number - 1
    else if (asize >= (dsize << ((list_number - 2) * (list_index)))) {
        return (list_number - 1);

    }
    // Normal
    else {
        for (size_t j = 1; j < list_number - 1; j++) {
            if (asize >= (dsize << (j * list_index - list_index)) &&
                (asize < dsize << (j * list_index)))
                return j;
        }
    }
    // Default
    return 0;
}

/**
 * @brief
 *
 * @functions: find_fit to find the suitable free block to alloc
 * @arguments: the size of the block
 * @precondition: asize should be the multiple of dsize
 * @param[in] asize
 * @return the block of the suitable space
 */
static block_t *find_fit(size_t asize) {
    // find the corresponding index for the block in our list array according
    // to its size
    size_t index = 0;
    index = get_index(asize);
    // pointer pointing at the best fit block
    block_t *best_fit = NULL;
    block_t *block;
    // assign a big number
    size_t best_fit_num = UINT64_MAX;

    // loop through all the blocks in lists to find the best fit block
    for (; index < list_number; index++) {
        block = seg_list[index];
        while (block) {
            if (!(get_alloc(block)) && (asize <= get_size(block))) {
                size_t diff = get_size(block) - asize;
                // when the size difference is zero, return the block pointer
                if (diff == 0x0)
                    return block;
                // mark the best fit block
                if (diff < best_fit_num) {
                    best_fit_num = diff;
                    best_fit = block;
                }
            }
            block = block->info.free_block.next;
        }
        // when find the best fit block, return the block pointer
        if (best_fit) {
            return best_fit;
        }
    }

    return NULL; // no fit found
}

/**
 * @brief
 *
 * @functions: check the block alignment, size, header and footer
 * @arguments: the pointer pointing at the block we are checking; the number of
 * line in our code
 * @preconditions: NULL
 * @param[in] line
 * @return false if error occurs; otherwise true
 */
bool check_block(block_t *bp, int line) {
    if ((get_size(bp) % dsize) != 0) {
        printf("---------------------\n");
        printf("Alignment Wrong at %d\n", line);
        return false;
    }
    if ((bp >= heap_start + 2 * dsize) && (get_size(bp) < min_block_size)) {
        printf("---------------------\n");
        printf("Size is too small at %d\n", line);
        return false;
    }
    if ((bp->header) != *(unsigned int *)(header_to_footer(bp))) {
        printf("---------------------\n");
        printf("Footer and Header is not equal at %d\n", line);
        return false;
    }
    return true;
}

/**
 * @brief
 *
 * @functions: check whether two block are freed but not coalescing
 * @arguments: the pointer pointing at the block we are checking; the number of
 * line in our code
 * @preconditions: NULL
 * @param[in] line
 * @return false if error occurs; otherwise true
 */
bool check_coalesce(block_t *bp, int line) {
    if ((get_alloc(bp) == false) && (get_alloc(find_next(bp)) == false)) {
        printf("---------------------\n");
        printf("bp: %p\n", bp);
        printf("No Coalesce at %d\n", line);
        return false;
    }
    return true;
}

/**
 * @brief
 *
 * @functions: check whether all elements are within the heap
 * @arguments: p1 the pointer pointing at the begining of our heap; p2 the
 * pointer pointing at the end of our heap; the number of line in our code
 * @preconditions: NULL
 * @param[in] line
 * @return false if error occurs; otherwise true
 */
bool check_boundry(void *p1, void *p2, int line) {
    if (p1 <= mem_heap_lo()) {
        printf("---------------------\n");
        printf("Low boundry wrong at %d\n", line);
        return false;
    }
    if (p2 >= mem_heap_hi()) {
        printf("---------------------\n");
        printf("High boundry wrong at %d\n", line);
        return false;
    }
    return true;
}

/**
 * @brief
 *
 * @functions: check the free list: boundry, seglist match
 * @arguments: the number of the block in heap; the number of line in our code
 * @preconditions: NULL
 * @param[in] line
 * @return false if error occurs; otherwise true
 */
bool check_freelist(size_t number, int line) {
    block_t *block;
    size_t temp_number = 0;
    for (size_t index = 0; index < list_number; index++) {
        block = seg_list[index];
        while (block != NULL) {
            if (block->info.free_block.next !=
                block->info.free_block.next->info.free_block.prev) {
                printf("---------------------\n");
                printf("Next or Prev inconsistent at %d\n", line);
                return false;
                if (!check_boundry(block->info.free_block.next,
                                   block->info.free_block.prev, line)) {
                    printf("---------------------\n");
                    printf("Pointers Boundry leaks at %d\n", line);
                    return false;
                }
                temp_number++;
                if (get_index(get_size(block)) != index) {
                    printf("---------------------\n");
                    printf("Seglist Size don't match at %d\n", line);
                    return false;
                }
                block = block->info.free_block.next;
            }
        }
    }
    if (temp_number != number) {
        printf("---------------------\n");
        printf("Count and Traversing don't match at %d\n", line);
    }
    return true;
}

/**
 * @brief
 *
 * @functions: check the prologue, block, coalesce, epilogue and boundry of the
 * heap
 * @arguments: the number of the line in code
 * @preconditions: NULL
 * @param[in] line
 * @return false if error occurs; otherwise true
 */
// bool mm_checkheap(int line) {
//     size_t block_number = 0;
//     block_t *bp;
//     // check prologue
//     if (!extract_alloc(*find_prev_footer(heap_start)) ||
//         extract_size(*find_prev_footer(heap_start)) != 0) {
//         printf("---------------------\n");
//         printf("Prologue Wrong at %d\n", line);
//         return false;
//     }
//     // check block and coalesce
//     for (bp = heap_start; get_size(bp) > 0; bp = find_next(bp)) {
//         if (!check_block(bp, line)) {
//             return false;
//         }
//         if (!check_coalesce(bp, line)) {
//             return false;
//         }
//         block_number++;
//     }
//     // check epilogue
//     if ((get_size(bp) != wsize) || !(get_alloc(bp))) {
//         printf("---------------------\n");
//         printf("Epilogue Wrong at %d\n", line);
//         return false;
//     }
//     // check free segregate list
//     if (!check_freelist(block_number, line)) {
//         return false;
//     }
//     // check boundry
//     if (!check_boundry(heap_start - 1, bp, line)) {
//         return false;
//     }
//     return true;
// }
bool mm_checkheap(int line) {
    /*
     * TODO: Delete this comment!
     *
     * You will need to write the heap checker yourself.
     * Please keep modularity in mind when you're writing the heap checker!
     *
     * As a filler: one guacamole is equal to 6.02214086 x 10**23 guacas.
     * One might even call it...  the avocado's number.
     *
     * Internal use only: If you mix guacamole on your bibimbap,
     * do you eat it with a pair of chopsticks, or with a spoon?
     */

    // heap level

    word_t prologue_footer;
    block_t *block = heap_start;
    prologue_footer = *(find_prev_footer(heap_start));

    // printf("Heap (%p):\n", heap_start);
    // prologue
    if (extract_size(prologue_footer) != 0 ||
        extract_alloc(prologue_footer) != 1) {
        printf("###############################################################"
               "####\n");
        printf("Bad prologue footer\n");
        printf("###############################################################"
               "####\n");
        return false;
    }

    // check each block
    bool pre_alloc_flag = 1;
    for (block = heap_start; get_size(block) > 0; block = find_next(block)) {

        // if(line) print_block(block);
        size_t size = get_size(block);
        if ((size % dsize) != 0) {
            printf("###########################################################"
                   "########\n");
            printf("Error: %p is not doubleword aligned\n", block);
            printf("###########################################################"
                   "########\n");
            return false;
        }
        if (!get_alloc(block)) {
            size_t footer_size = extract_size(*(header_to_footer(block)));

            if (size != footer_size ||
                (get_alloc(block) !=
                 extract_alloc(*(header_to_footer(block))))) {
                printf("#######################################################"
                       "####"
                       "########\n");
                printf("Error: header does not match footer\n");
                printf("#######################################################"
                       "####"
                       "########\n");
                return false;
            }
        }
        // check no free blocks are consecutive

        if (get_alloc(block) == 0 && pre_alloc_flag == 0) {
            printf("###########################################################"
                   "########\n");
            printf("Error: free blocks are consecutive\n");
            printf("###########################################################"
                   "########\n");
            return false;
        }
        pre_alloc_flag = get_alloc(block);
    }
    // epilogue
    if (extract_size(block->header) != 0 || extract_alloc(block->header) != 1) {
        printf("###############################################################"
               "####\n");
        printf("Bad epilogue header\n");
        printf("size=%lu\n", extract_size(block->header));
        printf("alloc=%d\n", extract_alloc(block->header));
        // CYPTODO: mem_heap_hi() 与epligue关系，而且还可能有错
        printf("%p\n", mem_heap_hi());
        printf("%p\n", block);
        printf("###############################################################"
               "####\n");
        return false;
    }

    // check free list
    // for (size_t class = 0; class < list_number; class ++) {
    //     block_t *temp = seg_list[class];
    //     while (temp != NULL) {
    //         block_t *pre_block = temp->info.free_block.prev;
    //         if (pre_block != NULL) {
    //             if (pre_block->info.free_block.next != temp) {
    //                 printf("###################################################"
    //                        "####"
    //                        "############\n");
    //                 printf("next/previous pointers are not consistent\n");
    //                 printf("###################################################"
    //                        "####"
    //                        "############\n");
    //                 return false;
    //             }
    //         }
    //         temp = temp->info.free_block.next;
    //     }
    // }

    // for (size_t class = 0; class < list_number; class ++) {
    //     block_t *temp = seg_list[class];

    //     size_t size = min_block_size << class;
    //     while (temp != NULL) {
    //         size_t block_size = get_size(temp);

    //         if (block_size > size) {
    //             printf("#######################################################"
    //                    "############\n");
    //             printf("blocks do not fall within bucket size range\n");
    //             printf("temp: %p\n", temp);
    //             printf("class number=%zu\n", class);
    //             printf("#######################################################"
    //                    "############\n");
    //             return false;
    //         }
    //         temp = temp->info.free_block.next;
    //     }
    // }

    // CYPTODO:All free list pointers are between mem heap lo() and mem heap
    // high().

    // Count free blocks by iterating through every block and traversing free
    // list by pointers and see if they match.

    // size_t free_block_count = 0;
    // for (block = heap_start; get_size(block) > 0; block = find_next(block)) {
    //     if (get_alloc(block) == 0)
    //         free_block_count++;
    // }

    // size_t free_list_count = 0;
    // for (size_t class = 0; class < list_number; class ++) {
    //     block_t *temp = seg_list[class];

    //     // printf("while count=%d\n", free_list_count);
    //     while (temp != NULL) {

    //         free_list_count++;

    //         temp = temp->info.free_block.next;
    //     }
    // }

    // if (free_block_count != free_list_count) {
    //     printf("###############################################################"
    //            "####\n");
    //     printf("free list numbers do not match\n");
    //     printf("free block count=%zu\n", free_block_count);
    //     printf("free list count=%zu\n", free_list_count);
    //     for (size_t class = 0; class < list_number; class ++) {
    //         if (seg_list[class] != NULL) {
    //             printf("-----class=%zu", class);
    //             printf("-----address=%p", seg_list[class]);
    //         }
    //     }
    //     printf("###############################################################"
    //            "####\n");
    //     return false;
    // }

    // no cycle linklist

    return true;
}

/**
 * @brief
 *
 * @functions: mm_init initialize the heap
 * @arguments: NULL
 * @preconditions: NULL
 * @return true if the heap initialize successfully
 */
bool mm_init(void) {

    // Create the initial empty heap
    word_t *start = (word_t *)(mem_sbrk(2 * wsize));

    if (start == (void *)-1) {
        return false;
    }

    start[0] = pack(0, true, true); // Heap prologue (block footer)
    start[1] = pack(0, true, true); // Heap epilogue (block header)

    // Heap starts with first "block header", currently the epilogue
    heap_start = (block_t *)&(start[1]);

    // Initialize the seg_list
    for (size_t i = 0; i < list_number; i++) {
        seg_list[i] = NULL;
    }

    // Extend the empty heap with a free block of chunksize bytes
    if (extend_heap(chunksize) == NULL) {
        return false;
    }

    return true;
}

/**
 * @brief
 *
 * @functions: malloc to alloc the block in the heap
 * @arguments: the size of the block we need to assign
 * @preconditions: NULL
 * @param[in] size
 * @return return the block pointer of the block we assign
 */
void *malloc(size_t size) {
    dbg_requires(mm_checkheap(__LINE__));

    size_t asize;      // Adjusted block size
    size_t extendsize; // Amount to extend heap if no fit is found
    block_t *block;
    void *bp = NULL;

    // Initialize heap if it isn't initialized
    if (heap_start == NULL) {
        mm_init();
    }

    // Ignore spurious request
    if (size == 0) {
        dbg_ensures(mm_checkheap(__LINE__));
        return bp;
    }

    // Adjust block size to include overhead and to meet alignment requirements
    asize = round_up(size + wsize, dsize);

    
    if (asize < dsize * 2) {
        asize = 2 * dsize;
    }
    // Search the free list for a fit
    block = find_fit(asize);

    // If no fit is found, request more memory, and then and place the block
    if (block == NULL) {
        // Always request at least chunksize
        extendsize = max(asize, chunksize);
        block = extend_heap(extendsize);
        // extend_heap returns an error
        if (block == NULL) {
            return bp;
        }
    }

    // The block should be marked as free
    dbg_assert(!get_alloc(block));

    // Mark block as allocated
    // size_t block_size = get_size(block);
    // write_header(block, block_size, true, true);
    // write_footer(block, block_size, true, true);

    // Try to split the block if too large
    split_block(block, asize);

    bp = header_to_payload(block);

    dbg_ensures(mm_checkheap(__LINE__));
    return bp;
}

/**
 * @brief
 *
 * @functions: free to free the allocated block
 * @arguments: the block pointer
 * @return NULL
 * @preconditions: NULL
 *
 * @param[in] bp
 */
void free(void *bp) {
    dbg_requires(mm_checkheap(__LINE__));

    if (bp == NULL) {
        return;
    }

    block_t *block = payload_to_header(bp);
    size_t size = get_size(block);

    // The block should be marked as allocated
    dbg_assert(get_alloc(block));

    // Mark the block as free
    bool prev_alloc = get_prev_alloc(block);
    write_header(block, size, false, prev_alloc);
    write_footer(block, size, false, prev_alloc);
    set_nextblock_prev_alloc(block, false);

    // Try to coalesce the block with its neighbors
    block = coalesce_block(block);

    dbg_ensures(mm_checkheap(__LINE__));
}

/**
 * @brief
 *
 * @functions: the implement of the realloc
 * @arguments: the block pointer and the size we need to assign
 * @preconditions: the pointer *ptr should be pointing at a block that has been
 * called malloc but has not been freed
 * @return NULL
 * @param[in] ptr
 * @param[in] size
 */
void *realloc(void *ptr, size_t size) {
    block_t *block = payload_to_header(ptr);
    size_t copysize;
    void *newptr;

    // If size == 0, then free block and return NULL
    if (size == 0) {
        free(ptr);
        return NULL;
    }

    // If ptr is NULL, then equivalent to malloc
    if (ptr == NULL) {
        return malloc(size);
    }

    // Otherwise, proceed with reallocation
    newptr = malloc(size);

    // If malloc fails, the original block is left untouched
    if (newptr == NULL) {
        return NULL;
    }

    // Copy the old data
    copysize = get_payload_size(block); // gets size of old payload
    if (size < copysize) {
        copysize = size;
    }
    memcpy(newptr, ptr, copysize);

    // Free the old block
    free(ptr);

    return newptr;
}

/**
 * @brief
 *
 * @functions: the implement of calloc
 * @arguments: size_t elements(the number of size we need to form a 2D block)
 *             size_t size(the size we want each element in the block has)
 * @pre: NULL
 * @param[in] elements
 * @param[in] size
 * @return NULL
 */
void *calloc(size_t elements, size_t size) {
    void *bp;
    size_t asize = elements * size;

    if (asize / elements != size) {
        // Multiplication overflowed
        return NULL;
    }

    bp = malloc(asize);
    if (bp == NULL) {
        return NULL;
    }

    // Initialize all bits to 0
    memset(bp, 0, asize);

    return bp;
}

/*
 *****************************************************************************
 * Do not delete the following super-secret(tm) lines!                       *
 *                                                                           *
 * 53 6f 20 79 6f 75 27 72 65 20 74 72 79 69 6e 67 20 74 6f 20               *
 *                                                                           *
 * 66 69 67 75 72 65 20 6f 75 74 20 77 68 61 74 20 74 68 65 20               *
 * 68 65 78 61 64 65 63 69 6d 61 6c 20 64 69 67 69 74 73 20 64               *
 * 6f 2e 2e 2e 20 68 61 68 61 68 61 21 20 41 53 43 49 49 20 69               *
 *                                                                           *
 * 73 6e 27 74 20 74 68 65 20 72 69 67 68 74 20 65 6e 63 6f 64               *
 * 69 6e 67 21 20 4e 69 63 65 20 74 72 79 2c 20 74 68 6f 75 67               *
 * 68 21 20 2d 44 72 2e 20 45 76 69 6c 0a c5 7c fc 80 6e 57 0a               *
 *                                                                           *
 *****************************************************************************
 */
