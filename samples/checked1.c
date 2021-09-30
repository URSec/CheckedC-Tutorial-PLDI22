#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#pragma CHECKED_SCOPE push

_Itype_for_any(T) void* malloc(size_t len) : itype(_Array_ptr<T>) byte_count(len);

_Itype_for_any(T) void free(void* ptr : itype(_Ptr<T>));

struct LinkedList {
    _Ptr<struct LinkedList> next;
    long val;
};

int main() {
    _Ptr<struct LinkedList> head = NULL, ptr = NULL, fptr = NULL;
    int i;
    head = malloc<struct LinkedList>(sizeof(struct LinkedList));

    ptr = head;
    for (i = 0; i < 5; ++i) {
        ptr->next = malloc<struct LinkedList>(sizeof(struct LinkedList));
        ptr = ptr->next;
        ptr->val = i;
    }

    ptr = head;
    for (i = 0; i < 6; ++i) {
        fptr = ptr;
        ptr = ptr->next;
        free<struct LinkedList>(fptr);
        printf("Address: %p, Value: %ld\n", ptr, ptr->val);
    }
    free<struct LinkedList>(ptr);

    return 0;
}

#pragma CHECKED_SCOPE pop
