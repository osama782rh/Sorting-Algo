#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "hybrid_sort.h"

#define INSERTION_SORT_THRESHOLD 16

void esiee_it_insertion_sort(char *arr, int low, int high) {
    for (int i = low + 1; i <= high; i++) {
        char key = arr[i];
        int j = i - 1;
        while (j >= low && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

int partition_hybrid(char *arr, int low, int high) {
    char pivot = arr[high];
    int i = low - 1;
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            char temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    char temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return (i + 1);
}

void heapify(char *arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;
    if (right < n && arr[right] > arr[largest])
        largest = right;
    if (largest != i) {
        char temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        heapify(arr, n, largest);
    }
}

void heap_sort(char *arr, int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
    for (int i = n - 1; i >= 0; i--) {
        char temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        heapify(arr, i, 0);
    }
}

void introsort_util(char *arr, int low, int high, int depth_limit) {
    int size = high - low + 1;
    if (size < INSERTION_SORT_THRESHOLD) {
        esiee_it_insertion_sort(arr, low, high);
        return;
    }
    if (depth_limit == 0) {
        heap_sort(arr + low, size);
        return;
    }
    int pivot = partition_hybrid(arr, low, high);
    introsort_util(arr, low, pivot - 1, depth_limit - 1);
    introsort_util(arr, pivot + 1, high, depth_limit - 1);
}

void esiee_it_sort(char *arr, int low, int high) {
    int depth_limit = 2 * log(high - low + 1);
    introsort_util(arr, low, high, depth_limit);
}
