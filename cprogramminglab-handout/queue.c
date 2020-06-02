/*
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q =  (queue_t *)malloc(sizeof(queue_t));
    /* What if malloc returned NULL? */
    if (q == NULL){
        return NULL;  // if no more memory, return NULL
        }
    q -> head = NULL; // head point to the box
    q -> tail = NULL; // tail point to the same box
    q -> size = 0; // make the size of box zero
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* How about freeing the list elements and the strings? */
    /* Free queue structure */
    if (q == NULL){
        return; // return nothing if q is NULL
    }
    list_ele_t *temp; //used to free the memory
    list_ele_t *point = NULL; // used as the index, move to the next structure
    temp = q -> head;
    while(temp){
        point = temp -> next; // point move to the next structure
        if (temp -> value){
            free(temp -> value); // if value in current structure, free them
            temp -> value = NULL;
            }
        free(temp); // free the structure
        temp = point; // move to the point, which is the next structure
        }
    q -> size = 0;
    free(q);
    q = NULL;
    temp = NULL;
    point = NULL;
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    list_ele_t *newh;
    /* What should you do if the q is NULL? */
    if (q == NULL){
        return false;
    }
    newh = (list_ele_t *)malloc(sizeof(list_ele_t));
    if (newh == NULL){
    	   free(newh); // if we can not allocate space, free it
        return false;
    }
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */
    newh -> value = (char *)malloc(strlen(s) + 1); 
/* 
allocate space for value, in order to store s. CAN NOT USE "sizeof" here.
sizeof(s) is not the proper way of getting the size of a string.
The problem is s is a char pointer, and the size of a pointer is 8 bytes.
Need to add 1 to store the terminator
*/
    if (newh -> value == NULL){
            free(newh -> value);
            free(newh);
            return false;
            }
    strcpy(newh -> value, s); // copy s to value
    newh -> next = q -> head; // new head attach to the original head
    q -> head = newh; // move queue head to new head
    if (q -> size == 0){ // if queue empty originally,
                         // head and tail point to the same element.
            q -> tail = newh;
            }
    q->size++; 
    return true;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    list_ele_t *newt = NULL;
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    if (q == NULL){
        return false;
    }
    newt = (list_ele_t *)malloc(sizeof(list_ele_t));
    if (newt == NULL){ // allocate space to new tail
    	   free(newt);
        return false;
    }
    newt -> value = (char *)malloc(strlen(s) + 1); // need to add 1 to store the terminator
    newt -> next = NULL;
    if (newt -> value == NULL){
        free(newt -> value);
        free(newt);
        newt = NULL;
        return false;
    }
    strcpy(newt->value, s);
    q -> tail -> next = newt; // new tail attach to the queue
    q -> tail = newt; // new tail becomes queue tail
    if (q -> size == 0){
            q -> head = q -> tail;
            }
    q -> size++;
    return true;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    list_ele_t *temp;
    /* You need to fix up this code. */
    if (q == NULL || q->size == 0){
        return false;
    }
    temp = q -> head;
    q -> head = temp -> next; // queue head move to next element
    if (sp != NULL && temp -> value){
    		strncpy(sp, temp -> value, bufsize-1);
    		sp[bufsize-1] = '\0'; // add a null terminator
    		}
    temp -> next = NULL; // remove old head
    free(temp -> value);
    free(temp); 
    q -> size--;
    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    if (q == NULL || q -> size == 0){
    		return 0;
    		}
    return q -> size;
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements                                  
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    list_ele_t *pre = NULL;
    list_ele_t *temp = NULL;
    list_ele_t *last = NULL;
    /* You need to write the code for this function */
    if (q == NULL || q -> size <= 1){
            return;
    } else {
        pre = q -> head; //pre point to the head
        temp = pre -> next; // temp next to head
        while (temp != NULL) {
            last = temp -> next; //last move to third one
            temp -> next = pre; // reverse
            pre = temp; //move pre
            temp = last; // move temp
        }
        q -> head -> next = NULL;
        q -> tail = q -> head;
        q -> head = pre;
        pre = NULL;
    }
    return;
}

