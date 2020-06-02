/*
 * Name: Peng Zeng
 * AndrewID: pengzeng
 *
 * This file is the header of the cache file.
 * The proxy.c only can use the function:
 * init_cache();
 * write_node();
 * free_list();
 * find_node();
 * get_node_value();
 */

#include "csapp.h"

#define MAX_CACHE_SIZE (1024 * 1024)
#define MAX_OBJECT_SIZE (100 * 1024)

/* The linked list node, which has the size, key, value and the pointer to the
 * next node and the previous node */
typedef struct node list_node;
struct node {
    size_t node_size;
    char *key;
    char *value;
    struct node *next;
    struct node *prev;
};

/* The linked list node, with the size of the whole list, the head pointer and
 * the tail pointer  */
typedef struct double_linked_list {
    size_t list_size;
    list_node *head;
    list_node *tail;
} DLlist;

DLlist *init_cache();
void write_node(DLlist *list, char *key, char *value, size_t size);
void free_list(DLlist *list);
list_node *find_node(DLlist *list, char *key);
char *get_value(DLlist *list, char *key, size_t *value_size);
