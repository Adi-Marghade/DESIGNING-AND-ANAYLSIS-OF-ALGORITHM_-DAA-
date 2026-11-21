#include <stdio.h>
#include <stdlib.h>


typedef struct {
    int *data;
    int size;
} Subset;

Subset *all_subsets = NULL;
int subset_count = 0;
int subset_capacity = 10;

// Function to store a valid subset to be printed later in reverse order
void store_subset(int *current_subset, int size) {
    if (subset_count >= subset_capacity) {
        subset_capacity *= 2;
        all_subsets = (Subset *)realloc(all_subsets, subset_capacity * sizeof(Subset));
    }
    all_subsets[subset_count].data = (int *)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        all_subsets[subset_count].data[i] = current_subset[i];
    }
    all_subsets[subset_count].size = size;
    subset_count++;
}

// Backtracking function
void find_subsets(int index, int n, int *arr, int target, int current_sum, int *current_subset, int subset_size) {
    // If target sum is reached, save the path
    if (current_sum == target) {
        store_subset(current_subset, subset_size);
        return;
    }
    
    // Base criteria to stop searching deeper
    if (index == n || current_sum > target) {
        return;
    }

    // Choice 1: Include the current element
    current_subset[subset_size] = arr[index];
    find_subsets(index + 1, n, arr, target, current_sum + arr[index], current_subset, subset_size + 1);

    // Choice 2: Exclude the current element
    find_subsets(index + 1, n, arr, target, current_sum, current_subset, subset_size);
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    int *arr = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) return 0;
    }

    int target;
    if (scanf("%d", &target) != 1) return 0;

    all_subsets = (Subset *)malloc(subset_capacity * sizeof(Subset));
    int *current_subset = (int *)malloc(n * sizeof(int));

    // Run backtracking algorithm
    find_subsets(0, n, arr, target, 0, current_subset, 0);

    // If no subsets were found, print -1
    if (subset_count == 0) {
        printf("-1\n");
    } else {
        // Print all subsets in reverse order of discovery
        for (int i = subset_count - 1; i >= 0; i--) {
            for (int j = 0; j < all_subsets[i].size; j++) {
                printf("%d", all_subsets[i].data[j]);
                if (j < all_subsets[i].size - 1) {
                    printf(" ");
                }
            }
            printf(" \n");
            free(all_subsets[i].data);
        }
    }

    // Free all allocated memory
    free(all_subsets);
    free(current_subset);
    free(arr);

    return 0;
}
