#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdchecked.h>

#define NODE_SIZE 5
#define VAL_SIZE 3

/**
 * Useful tips for porting this program.
 *
 * 1. Checked C provides several aliases for its new keywords. Beblow are
 * several that you may use in this tutorial:
 *
 *   #define ptr _Ptr
 *   #define array_ptr _Array_ptr
 *   #define checked _Checked
 *
 * 2. How to declare the bounds for an array pointer:
 *    1. array_ptr<T> p : count(bounds_expr) = ...;
 *    2. array_ptr<T> p : bounds(lower_b, upper_b) = ...
 *
 * 3. The bounds-safe interfaces for malloc and free are defined as follows:
 *
 *    _Itype_for_any(T) void* malloc(size_t len) : itype(_Array_ptr<T>) byte_count(len);
 *    _Itype_for_any(T) void free(void* p : itype(_Ptr<T>));
 *
 *    They take a type parameter; so you need provide a type paramter when
 *    calling them, e.g., "... = malloc<int>(...);".
 * 
 * 4. Variadic functions such as printf are inherently unsafe and thus cannot
 *    be used in checked regions.
 * */

struct LinkedList {
    struct LinkedList *next;
    long *vals;
};

/* Print the vals of a node of the linked list. */
void print_linkedlist(struct LinkedList *p) {
    for (unsigned j = 0; j < VAL_SIZE; j++) {
        printf("%ld ", p->vals[j]);
    }
    printf("\n");
}

int main() {
    struct LinkedList *head, *curr, *next;
    head = malloc(sizeof(struct LinkedList));

    /* Initialize the linked list */
    curr = head;
    for (unsigned i = 0; i < NODE_SIZE; ++i) {
        curr->next = malloc(sizeof(struct LinkedList));
        curr->vals = malloc(sizeof(long) * VAL_SIZE);
        for (unsigned j = 0; j < VAL_SIZE; ++j) {
            curr->vals[j] = i + j;
        }
        curr = curr->next;
    }
    curr->next = NULL;

    /* Print out the linked list */
    curr = head;
    for (unsigned i = 0; i < NODE_SIZE; i++) {
        printf("Node_%u: ", i);
        print_linkedlist(curr);
        curr = curr->next;
    }

    /* Free the the linkedlist */
    curr = head;
    for (unsigned i = 1; i < NODE_SIZE; ++i) {
        next = curr->next;
        free(curr->vals);
        free(curr);
        curr = next;
    }
    free(next);

    return 0;
}
