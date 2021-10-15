/**
 * sum2array.c
 * */

#include <stdio.h>

/**
 * Function: sum2array
 * A simple function that sums up two arrays and stores the results to the
 * first array.
 * */
void sum2array(int *arr1, int *arr2, int size) {
    for (int i = 0; i < size; i++) {
        arr1[i] = arr1[i] + arr2[i];
    }
}

/*
 * Entrance of this program.
 * */
int main(int argc, char *argv[]) {
    int arr1[5] = {
        1, 2, 3, 4, 5
    };
    int arr2[5] = {
        6, 7, 8, 9, 10
    };

    sum2array(arr1, arr2, 5);

    /* Print the result of the summed array1 */
    printf("Updated array1:\n");
    for (int i = 0; i < 5; i++) {
        printf("%d\n", arr1[i]);
    }

    return 0;
}
