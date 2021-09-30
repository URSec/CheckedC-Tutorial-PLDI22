#include <stdio.h>
#include <stdlib.h>

struct LinkedList {
    struct LinkedList *next;
    long val;
};

int main() {
    struct LinkedList head;
    struct LinkedList *ptr, *fptr;
    int i;

    ptr = &head;
    for (i = 0; i < 5; ++i) {
        ptr->next = malloc(sizeof(struct LinkedList));
        ptr = ptr->next;
        ptr->val = i;
    }

    ptr = &head;
    for (i = 0; i < 5; ++i) {
        fptr = ptr;
        ptr = ptr->next;
        free(fptr);
        printf("Address: %p, Value: %ld\n", ptr, ptr->val);
    }

    return 0;
}
