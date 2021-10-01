#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

/*
 * This is the provided bounds-safe interface definition for malloc() and * free().

_Itype_for_any(T) void* malloc(size_t len) : itype(_Array_ptr<T>) byte_count(len);

_Itype_for_any(T) void free(void* ptr : itype(_Ptr<T>));

*/

struct LinkedList {
    struct LinkedList *next;
    long val;
};

int main() {
    struct LinkedList *head, *ptr, *fptr;
    int i;
    long val;
    head = malloc(sizeof(struct LinkedList));

    ptr = head;
    for (i = 0; i < 5; ++i) {
        ptr->next = malloc(sizeof(struct LinkedList));
        ptr = ptr->next;
        ptr->val = i;
    }

    ptr = head;
    for (i = 0; i < 5; ++i) {
        fptr = ptr;
        ptr = ptr->next;
        free(fptr);
        val = ptr->val;

        printf("Address: %p, Value: %ld\n", ptr, val);
    }
    free(ptr);

    return 0;
}
