/**
 * @file mm.c
 * @brief A 64-bit struct-based implicit free list memory allocator
 *
 * 15-213: Introduction to Computer Systems
 *
 * TODO: insert your documentation here. :)
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

static const size_t list_number = 10;

static const size_t list_range = 1;

/**
 * size_mask to get the size bits of the block
 */
static const word_t size_mask = ~(word_t)0xF;

/** @brief Represents the header and payload of one block in the heap */
typedef struct block {
    /** @brief Header contains size + allocation flag */
    word_t header;
    union {
        struct {
            struct block *next;
            struct block *prev;
        } free_block;
        char payload[0];
    } info;
} block_t;

/* Global variables */

/** @brief Pointer to first block in the heap */
static block_t *heap_start = NULL;

static block_t *seg_list[list_number];

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
static void write_footer(block_t *block, size_t size, bool alloc);
static size_t hash(size_t asize);
static void delete_block(block_t *block);
static void insert_block(block_t *block);

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
static word_t pack(size_t size, bool alloc) {
    word_t word;
    if (alloc) {
        word = (size | alloc_mask);
    } else {
        word = size;
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
    block_t *prev_block = find_prev(block);
    return extract_alloc(prev_block->header);
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

/**
 * @brief Writes an epilogue header at the given address.
 *
 * The epilogue header has size 0, and is marked as allocated.
 *
 * @param[out] block The location to write the epilogue header
 */
static void write_epilogue(block_t *block) {
    dbg_requires(block != NULL);
    dbg_requires((char *)block == mem_heap_hi() - 7);
    block->header = pack(0, true);
}

/**
 * @brief Writes a block starting at the given address.
 *
 * This function writes both a header and footer, where the location of the
 * footer is computed in relation to the header.
 *
 * TODO: Are there any preconditions or postconditions?
 *
 * @param[out] block The location to begin writing the block header
 * @param[in] size The size of the new block
 * @param[in] alloc The allocation status of the new block
 */
static void write_block(block_t *block, size_t size, bool alloc) {
    dbg_requires(block != NULL);
    dbg_requires(size > 0);
    block->header = pack(size, alloc);
    word_t *footerp = header_to_footer(block);
    *footerp = pack(size, alloc);
}

static void write_header(block_t *block, size_t size, bool alloc) {
    dbg_requires(block != NULL);
    block->header = pack(size, alloc);
}

static void write_footer(block_t *block, size_t size, bool alloc) {
    dbg_requires(block != NULL);
    dbg_requires(get_size(block) == size && size > 0);
    word_t *footerp = header_to_footer(block);
    *footerp = pack(size, alloc);
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
static block_t *find_prev(block_t *block) {
    dbg_requires(block != NULL);
    dbg_requires(get_size(block) != 0);
    word_t *footerp = find_prev_footer(block);
    return footer_to_header(footerp);
}

// 分配下一个block的前一个block的分配情况
// static void set_nextblock_pre_alloc(block_t *block, bool prev_alloc) {
//     block_t *next_block = find_next(block);
//     size_t next_size = get_size(next_block);
//     bool next_alloc = get_next_alloc(block);
//     write_header(next_block, next_size, next_alloc);
// }

// 分配前一个block的下一个block的分配情况
// static void set_prevblock_next_alloc(block_t *block, bool next_alloc) {
//     block_t *prev_block = find_prev(block);
//     size_t prev_size = get_size(prev_block);
//     bool prev_alloc = get_prev_alloc(block);
//     write_header(prev_block, prev_size, prev_alloc, next_alloc);
// }

/*
 * ---------------------------------------------------------------------------
 *                        END SHORT HELPER FUNCTIONS
 * ---------------------------------------------------------------------------
 */

/******** The remaining content below are helper and debug routines ********/

/**
 * @brief
 *
 * <What does this function do?>
 * <What are the function's arguments?>
 * <What is the function's return value?>
 * <Are there any preconditions or postconditions?>
 *
 * @param[in] block
 * @return
 */
static block_t *coalesce_block(block_t *block) {
    dbg_requires(!get_alloc(block));
    size_t size = get_size(block);

    block_t *next_block = find_next(block);
    block_t *prev_block = find_prev(block);

    bool next_alloc = get_alloc(next_block);
    bool prev_alloc = get_alloc(prev_block);
    // Case 1
    // Previous and next alloc
    if (next_alloc && prev_alloc) {
        insert_block(block);
        // set_nextblock_pre_alloc(block, false);
    }
    // Case 2
    // Previous alloc and next not alloc
    // Coalesce next block
    else if (prev_alloc && !next_alloc) {
        size += get_size(next_block);
        delete_block(next_block);
        write_header(block, size, false);
        write_footer(block, size, false);
        insert_block(block);
        // set_nextblock_pre_alloc(block, false);
    }
    // Case 3
    // Previous not alloc and next alloc
    // Coalesce previous block
    else if (!prev_alloc && next_alloc) {
        size += get_size(prev_block);
        delete_block(prev_block);
        write_header(prev_block, size, false);
        write_footer(prev_block, size, false);
        // set_nextblock_pre_alloc(block, false);
        block = prev_block;
        insert_block(block);
    }
    // Case 4
    // Coalesce both previous and next
    else {
        size += get_size(prev_block);
        size += get_size(next_block);
        delete_block(prev_block);
        delete_block(next_block);
        write_header(prev_block, size, false);
        write_footer(prev_block, size, false);
        // set_nextblock_pre_alloc(prev_block, false);
        block = prev_block;
        insert_block(block);
    }
    // insert_block(block);
    dbg_ensures(!get_alloc(block));
    return block;
}

/**
 * @brief
 *
 * <What does this function do?>
 * <What are the function's arguments?>
 * <What is the function's return value?>
 * <Are there any preconditions or postconditions?>
 *
 * @param[in] size
 * @return
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
    write_header(block, size, false);
    write_footer(block, size, false);

    // Create new epilogue header
    block_t *next_block = find_next(block);
    write_header(next_block, 0, true);

    // Coalesce in case the previous block was free
    block = coalesce_block(block);

    return block;
}

/**
 * @brief
 *
 * <What does this function do?>
 * <What are the function's arguments?>
 * <What is the function's return value?>
 * <Are there any preconditions or postconditions?>
 *
 * @param[in] block
 * @param[in] asize
 */
static void split_block(block_t *block, size_t asize) {
    dbg_requires(get_alloc(block));
    /* TODO: Can you write a precondition about the value of asize? */

    size_t block_size = get_size(block);

    delete_block(block);

    if ((block_size - asize) >= min_block_size) {
        block_t *next_block;
        write_header(block, asize, true);
        write_footer(block, asize, true);

        next_block = find_next(block);
        write_header(next_block, block_size - asize, false);
        write_footer(next_block, block_size - asize, false);

        insert_block(next_block);
    }

    dbg_ensures(get_alloc(block));
}

static void delete_block(block_t *block) {
    if (block == NULL) {
        return;
    }

    size_t index = 0;
    size_t asize;
    asize = round_up(get_size(block), dsize);
    index = hash(asize);

    if (!block->info.free_block.prev && !block->info.free_block.next) {
        seg_list[index] = NULL;
    }
    if (!block->info.free_block.prev) {
        block_t *next_block = block->info.free_block.next;
        next_block->info.free_block.prev = NULL;
        seg_list[index] = next_block;
        return;
    }
    if (!block->info.free_block.next) {
        block_t *prev_block = block->info.free_block.prev;
        prev_block->info.free_block.next = NULL;
        return;
    }
    block_t *next_block = block->info.free_block.next;
    block_t *prev_block = block->info.free_block.prev;
    prev_block->info.free_block.next = next_block;
    next_block->info.free_block.prev = prev_block;
    return;
}

static void insert_block(block_t *block) {
    if (!block) {
        return;
    }
    size_t index = 0;
    size_t asize;
    asize = round_up(get_size(block), dsize);
    index = hash(asize);
    if (!seg_list[index]) {
        seg_list[index] = block;
        block->info.free_block.next = NULL;
        block->info.free_block.prev = NULL;
        return;
    } else {
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
 * <What does this function do?>
 * <What are the function's arguments?>
 * <What is the function's return value?>
 * <Are there any preconditions or postconditions?>
 *
 * @param[in] asize
 * @return
 */
// static block_t *find_fit(size_t asize) {
//     block_t *block;

//     for (block = heap_start; get_size(block) > 0; block = find_next(block)) {

//         if (!(get_alloc(block)) && (asize <= get_size(block))) {
//             return block;
//         }
//     }
//     return NULL; // no fit found
// }

static size_t hash(size_t asize) {
    size_t j;

    // for small size
    if (asize < dsize) {
        return 0;
        // for very large size
    } else if (asize >= (dsize << ((list_number - 2) * (list_range)))) {
        return (list_number - 1);
        // for other normal size
    } else {
        for (j = 1; j < list_number - 1; j++) {
            if (asize >= (dsize << (j * list_range - list_range)) &&
                (asize < dsize << (j * list_range)))
                return j;
        }
    }
    // default
    return 0;
}

static block_t *find_fit(size_t asize) {
    // find the corresponding index for the block in our list array according
    // to its size
    size_t index = 0;
    index = hash(asize);
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
 * <What does this function do?>
 * <What are the function's arguments?>
 * <What is the function's return value?>
 * <Are there any preconditions or postconditions?>
 *
 * @param[in] line
 * @return
 */
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

    return true;
}

/**
 * @brief
 *
 * <What does this function do?>
 * <What are the function's arguments?>
 * <What is the function's return value?>
 * <Are there any preconditions or postconditions?>
 *
 * @return
 */
bool mm_init(void) {

    for (size_t i = 0; i < list_number; i++) {
        seg_list[i] = NULL;
    }
    // Create the initial empty heap
    word_t *start = (word_t *)(mem_sbrk(2 * wsize));

    if (start == (void *)-1) {
        return false;
    }

    start[0] = pack(0, true); // Heap prologue (block footer)
    start[1] = pack(0, true); // Heap epilogue (block header)

    // Heap starts with first "block header", currently the epilogue
    heap_start = (block_t *)&(start[1]);

    // Extend the empty heap with a free block of chunksize bytes
    if (extend_heap(chunksize) == NULL) {
        return false;
    }

    return true;
}

/**
 * @brief
 *
 * <What does this function do?>
 * <What are the function's arguments?>
 * <What is the function's return value?>
 * <Are there any preconditions or postconditions?>
 *
 * @param[in] size
 * @return
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
    asize = round_up(size + dsize, dsize);

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
    size_t block_size = get_size(block);
    write_header(block, block_size, true);
    write_footer(block, block_size, true);

    // Try to split the block if too large
    split_block(block, asize);

    bp = header_to_payload(block);

    dbg_ensures(mm_checkheap(__LINE__));
    return bp;
}

/**
 * @brief
 *
 * <What does this function do?>
 * <What are the function's arguments?>
 * <What is the function's return value?>
 * <Are there any preconditions or postconditions?>
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
    write_header(block, size, false);
    write_footer(block, size, false);

    // Try to coalesce the block with its neighbors
    block = coalesce_block(block);

    dbg_ensures(mm_checkheap(__LINE__));
}

/**
 * @brief
 *
 * <What does this function do?>
 * <What are the function's arguments?>
 * <What is the function's return value?>
 * <Are there any preconditions or postconditions?>
 *
 * @param[in] ptr
 * @param[in] size
 * @return
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
 * <What does this function do?>
 * <What are the function's arguments?>
 * <What is the function's return value?>
 * <Are there any preconditions or postconditions?>
 *
 * @param[in] elements
 * @param[in] size
 * @return
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
