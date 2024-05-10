#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BUFFER_SIZE 64

void print_list(int* list, int length) {
    for (int i=0; i<length; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");
}

void shift_swap(int* list, int low, int high) {
    int tmp = list[high];

    for (int i=high; i>low; i--) {
        list[i] = list[i-1];
    }
    list[low] = tmp;
}

void quick_sort(int* list, int low, int high, int length) {
    int pivot_index = low;

    // if only 1 element is left; OR if only 2 elements are left, they are sured to be already sorted from previous iteration
    if (high - low == 0 || high - low == 1) return;

    for (int i=low; i<high; i++) {
        if (list[pivot_index] > list[i]) {
            shift_swap(list, pivot_index, i);
            pivot_index++;
        }
    }
    
    //print_list(list,length);
    quick_sort(list, low, pivot_index, length);  // left of pivot
    quick_sort(list, pivot_index+1, high, length); // right of pivot
}


int main() {
    clock_t start, end;
    double cpu_time_used;

    /*
    // count the number of lines
    int integers = 0;
    file = fopen("list.txt", "r");

    while (fgets(buffer, BUFFER_SIZE, file) != NULL) {
        integers++;
    }

    fclose(file);
    */

    start = clock();

    int length = 100000, counter=0;
    int unsorted_list[100000];

    char buffer[BUFFER_SIZE];
    int number;
    FILE* file = fopen("list.txt", "r");

    if (file == NULL) {
        printf("Failed to open the file.\n");
        return 1;
    }

    while (fgets(buffer, BUFFER_SIZE, file) != NULL) {
        if (sscanf(buffer, "%d", &number) == 1) {
            unsorted_list[counter] = number;
            counter++;
        } else {
            printf("Error: Non-integer character detected.\n");
        }
    }


    //print_list(unsorted_list, length);
    quick_sort(unsorted_list, 0, length, length);
    //print_list(unsorted_list, length);   

    fclose(file);

    file = fopen("sorted_list.txt", "w");
    if (file == NULL) {
        printf("Failed to create file.");
        return 1;
    }

    for (int i=0; i<length; i++) {
        fprintf(file, "%d\n", unsorted_list[i]); // poor naming, it has been sorted after quick_sort() finished.
    }

    fclose(file);

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("\nCPU time used: %f seconds\n", cpu_time_used);

    return 0;
}