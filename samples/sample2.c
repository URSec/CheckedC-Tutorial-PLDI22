#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void foo(char* a, char* b) {
    int len_a = strnlen(a, 255);
    int len_b = strnlen(b, 255);
    char* s1 = malloc(len_a);
    strncpy(s1, a, len_a);

    char* s2 = malloc(len_b);
    strncpy(s2, b, len_b);

    strncpy(s1, s2, len_b);
    s1[len_b] = '\0';

    printf("s1: %s\ns2: %s\n", s1, s2);

    free(s1);
    free(s2);
}

int main() {
    foo("Hello, World", "SecDev");
    return 0;
}
