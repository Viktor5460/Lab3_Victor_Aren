#include <stdio.h>
#include <stdlib.h>

// Merging two halves of the array
void merge(int arr[], int left, int mid, int right, int iteration) {
    int n1 = mid - left + 1; // Size of left subarray
    int n2 = right - mid;    // Size of right subarray

    // Create temporary arrays
    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    // Copy data to temporary arrays L[] and R[]
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    // Merge the temporary arrays back into arr[left..right]
    int i = 0; // Initial index of first subarray
    int j = 0; // Initial index of second subarray
    int k = left; // Initial index of merged subarray

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], if there are any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if there are any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    // Create an output file for the current iteration
    char filename[30];
    snprintf(filename, sizeof(filename), "merge_iteration_%d.txt", iteration);
    FILE *outputFile = fopen(filename, "w");
    if (outputFile == NULL) {
        fprintf(stderr, "Error opening output file for iteration %d\n", iteration);
        exit(1);
    }

    // Write the current state of the array to the output file
    for (int m = 0; m <= right; m++) {
        fprintf(outputFile, "%d\n", arr[m]);
    }

    // Close the output file
    fclose(outputFile);

    // Free temporary arrays
    free(L);
    free(R);
}

// Recursive merge sort function
void mergeSort(int arr[], int left, int right, int *iteration) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        // Sort first and second halves
        mergeSort(arr, left, mid, iteration);
        mergeSort(arr, mid + 1, right, iteration);

        // Merge the sorted halves
        (*iteration)++;
        merge(arr, left, mid, right, *iteration);
    }
}

int main() {
    FILE *inputFile;
    int *arr = NULL;
    int num, count = 0, capacity = 10;
    int iteration = 0;

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
    mergeSort(arr, 0, count - 1, &iteration);

    // Free allocated memory
    free(arr);

    printf("Sorting completed. Check the iteration files for results.\n");
    return 0;
}