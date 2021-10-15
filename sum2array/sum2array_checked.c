/**
 * sum2array_checked.c
 * */

#include <stdio.h>

/**
 * Function: sum2array
 * A simple function that sums up two arrays and stores the results to the
 * first array.
 * */
void sum2array(_Array_ptr<int> arr1 : count(size),
               _Array_ptr<int> arr2 : count(size), int size) {
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

    _Array_ptr<int> p_arr1 : count(5) = arr1;
    _Array_ptr<int> p_arr2 : count(5) = arr2;

    sum2array(p_arr1, p_arr2, 5);

    /* Print the result of the summed array1 */
    printf("Updated array1:\n");
    for (int i = 0; i < 5; i++) {
        printf("%d\n", p_arr1[i]);
    }

    return 0;
}
