#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdchecked.h>

#define NODE_SIZE 5
#define VAL_SIZE 3

struct LinkedList {
    ptr<struct LinkedList> next;
    array_ptr<long> vals : count(VAL_SIZE);
};

/* Print the vals of a node of the linked list. */
void print_linkedlist(array_ptr<long> p_vals : count(VAL_SIZE)) {
    for (unsigned i = 0; i < VAL_SIZE; i++) {
        printf("%ld ", p_vals[i]);
    }
    printf("\n");
}

int main() {
    ptr<struct LinkedList> head = NULL, curr = NULL, next = NULL;
    head = malloc<struct LinkedList>(sizeof(struct LinkedList));

    /* Initialize the linked list */
    curr = head;
    for (unsigned i = 0; i < NODE_SIZE; ++i) {
        curr->next = malloc<struct LinkedList>(sizeof(struct LinkedList));
        curr->vals = malloc<struct LinkedList>(sizeof(long) * VAL_SIZE);
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
        print_linkedlist(curr->vals);
        curr = curr->next;
    }

    /* Free the nodes of the linked list */
    curr = head;
    for (unsigned i = 1; i < NODE_SIZE; ++i) {
        next = curr->next;
        free<long>(curr->vals);
        free<struct LinkedList>(curr);
        curr = next;
    }
    free<struct LinkedList>(next);

    return 0;
}
