#include <stdio.h>
#include <stdlib.h>

int partition(int arr[], int low, int high, int iteration) {
    int pivot = arr[high]; // pivot
    int i = (low - 1); // Index of smaller element

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++; // increment index of smaller element
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    // Swap the pivot element with the element at index i+1
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    // Create an output file for the current iteration
    char filename[30];
    snprintf(filename, sizeof(filename), "iteration_%d.txt", iteration);
    FILE *outputFile = fopen(filename, "w");
    if (outputFile == NULL) {
        fprintf(stderr, "Error opening output file for iteration %d\n", iteration);
        exit(1);
    }

    // Write the current state of the array to the output file with line numbers
    for (int k = 0; k <= high; k++) {
        fprintf(outputFile, "%d %d\n", k + 1, arr[k]); // Line number and value
    }

    // Close the output file
    fclose(outputFile);

    return i + 1; // Return the partition index
}

void quickSort(int arr[], int low, int high, int *iteration) {
    if (low < high) {
        // Partitioning index
        int pi = partition(arr, low, high, (*iteration)++);

        // Recursively sort elements before and after partition
        quickSort(arr, low, pi - 1, iteration);
        quickSort(arr, pi + 1, high, iteration);
    }
}

int main() {
    FILE *inputFile;
    int *arr = NULL;
    int num, count = 0, capacity = 10;
    int iteration = 1; // Start iteration count from 1

    // Allocate initial memory for the array
    arr = (int *)malloc(capacity * sizeof(int));
    if (arr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Open input file for reading
    inputFile = fopen("numbers.txt", "r");
    if (inputFile == NULL) {
        fprintf(stderr, "Error opening input file\n");
        free(arr);
        return 1;
    }

    // Read numbers from file
    while (fscanf(inputFile, "%d", &num) == 1) {
        if (count >= capacity) {
            // Resize the array if needed
            capacity *= 2;
            arr = (int *)realloc(arr, capacity * sizeof(int));
            if (arr == NULL) {
                fprintf(stderr, "Memory reallocation failed\n");
                fclose(inputFile);
                return 1;
            }
        }
        arr[count++] = num;
    }

    // Close the input file
    fclose(inputFile);

    // Sort the array and output each iteration
    quickSort(arr, 0, count - 1, &iteration);

    // Free allocated memory
    free(arr);

    printf("Sorting completed. Check the iteration files for results.\n");
    return 0;
}
