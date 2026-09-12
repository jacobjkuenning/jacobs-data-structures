#pragma once
#include <stdlib.h>

// sort array using the heap sort algorithm
void heap_sort(void* arr, int n, size_t size, int(*cmp) (const void* a, const void* b));

// structurally turn unsorted array into heap
void build_heap(void* arr, int n, size_t size, int (*cmp) (const void* a, const void* b));

// turn array into a heap data structure
void heapify(void* arr, int i, int n, size_t size, int (*cmp) (const void* a, const void* b));

