#include <stdio.h>
#include <stdlib.h>

void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;

        // Find the minimum element in the unsorted array
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }

        // Swap the found minimum element with the first element
        int temp = arr[minIndex];
        arr[minIndex] = arr[i];
        arr[i] = temp;

        // Create an output file for the current iteration
        char filename[30];
        snprintf(filename, sizeof(filename), "iteration_%d.txt", i + 1);
        FILE *outputFile = fopen(filename, "w");
        if (outputFile == NULL) {
            fprintf(stderr, "Error opening output file for iteration %d\n", i + 1);
            exit(1);
        }

        // Write the current state of the array to the output file with line numbers
        for (int k = 0; k < n; k++) {
            fprintf(outputFile, "%d %d\n", k + 1, arr[k]); // Line number and value
        }

        // Close the output file
        fclose(outputFile);
    }
}

int main() {
    FILE *inputFile;
    int *arr = NULL;
    int num, count = 0, capacity = 10;

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

    // Read numbers from the file
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
    selectionSort(arr, count);

    // Free allocated memory
    free(arr);

    printf("Sorting completed. Check iteration files for results.\n");
    return 0;
}
