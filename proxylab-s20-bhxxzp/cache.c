/*
 * Name: Peng Zeng
 * AndrewID: pengzeng
 *
 * This is the c file of the cache. I implement the cache with the double linked
 * list. The linked list has two empty node at first, which is the head and tail
 * of the linked list. Then the node with some specific key and value will be
 * stored between the head and tail. The linked list implements the LRU policy
 * and update the head next node when we use some node at some time.
 */

#include "cache.h"
#include "csapp.h"

#include <assert.h>
#include <ctype.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>

#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <pthread.h>
#include <signal.h>
#include <sys/socket.h>
#include <sys/types.h>

static pthread_mutex_t mutex;
void delete_node(DLlist *list, list_node *node);
list_node *create_node(char *key, char *value, size_t size);
list_node *create_empty_node();

/* Initialize the double linked list */
DLlist *init_cache() {
    DLlist *list = (DLlist *)Malloc(sizeof(DLlist));
    list->list_size = 0;

    list_node *head_node = create_empty_node(); /* Head node */
    list->head = head_node;

    list_node *tail_node = create_empty_node(); /* Tail node */
    list->tail = tail_node;

    list->head->next = list->tail;
    list->tail->prev = list->head;

    /* Initialize the lock */
    pthread_mutex_init(&mutex, NULL);
    return list;
}

/* Create the empty node when we initialize the list */
list_node *create_empty_node() {
    list_node *node = (list_node *)Malloc(sizeof(list_node));
    node->node_size = 0;
    node->key = NULL;
    node->value = NULL;
    node->prev = NULL;
    node->next = NULL;
    return node;
}

/* Free the list */
void free_list(DLlist *list) {
    list_node *temp = list->head->next;
    while (temp) {
        list_node *temp_next = temp->next;
        delete_node(list, temp);
        temp = temp_next;
    }
    Free(list->head);
    Free(list->tail);
    Free(list);
}

/* Find the node which key is what we want */
list_node *find_node(DLlist *list, char *key) {
    for (list_node *output = list->head->next; output != list->tail;
         output = output->next) {
        if (strcmp(key, output->key) == 0) {
            output->next->prev = output->prev;
            output->prev->next = output->next;
            list->head->next->prev = output;
            output->next = list->head->next;
            list->head->next = output;
            output->prev = list->head;
            return output;
        }
    }
    return NULL;
}

/* Write the node using the input key and value, and then store into the linked
 * list */
void write_node(DLlist *list, char *key, char *value, size_t size) {
    bool has_key = false;
    for (list_node *temp = list->head->next; temp != list->tail;
         temp = temp->next) {
        if (strcmp(key, temp->key) == 0) {
            has_key = true;
            break;
        }
    }
    if (has_key) {
        return;
    }
    pthread_mutex_lock(&mutex);

    list_node *new_node = create_node(key, value, size);
    if (list->list_size + size <= MAX_CACHE_SIZE) {
        list->list_size += new_node->node_size;
        list->head->next->prev = new_node;
        new_node->next = list->head->next;
        list->head->next = new_node;
        new_node->prev = list->head;
    } else {
        list_node *lastone = list->tail->prev;
        while (lastone) {
            list_node *last_prev = lastone->prev;
            delete_node(list, lastone);
            if (list->list_size + new_node->node_size <= MAX_CACHE_SIZE) {
                list->list_size += new_node->node_size;
                list->head->next->prev = new_node;
                new_node->next = list->head->next;
                list->head->next = new_node;
                new_node->prev = list->head;
                pthread_mutex_unlock(&mutex);
                return;
            }
            lastone = last_prev;
        }
    }
    pthread_mutex_unlock(&mutex);
    return;
}

/* Get the value of the node with the specific key */
char *get_value(DLlist *list, char *key, size_t *value_size) {
    pthread_mutex_lock(&mutex);
    list_node *temp = find_node(list, key);
    if (temp == NULL) {
        pthread_mutex_unlock(&mutex);
        return NULL;
    }
    *value_size = temp->node_size;
    char *output = (char *)Malloc(sizeof(char) * (temp->node_size));
    memcpy(output, temp->value, sizeof(char) * (temp->node_size));
    pthread_mutex_unlock(&mutex);
    return output;
}

/* Create the node with specific key, value and size */
list_node *create_node(char *key, char *value, size_t size) {
    list_node *new_node = (list_node *)Malloc(sizeof(list_node));

    /* Initialize the node size */
    new_node->node_size = size;

    /* Initialize the node key */
    new_node->key = (char *)Malloc(sizeof(char) * (strlen(key) + 1));
    memcpy(new_node->key, key, sizeof(char) * (strlen(key) + 1));

    /* Initialize the node value */
    new_node->value = (char *)Malloc(sizeof(char) * size);
    memcpy(new_node->value, value, sizeof(char) * size);

    new_node->next = NULL;
    new_node->prev = NULL;

    return new_node;
}

/* Delete the node in the linked list */
void delete_node(DLlist *list, list_node *node) {
    list->list_size -= node->node_size;
    node->prev->next = node->next;
    node->next->prev = node->prev;
    Free(node->key);
    Free(node->value);
    Free(node);
    return;
}
