#pragma once
#include "../data-structures/darray.h"

// pick random element and sort it into place, returning it's position
int partition(void* arr, int left, int right, size_t size, int (*cmp)(void* a, void* b));

// sort an array using the quick sort algorithm. NOTE: if using a darray, pass in darr->elements
void quick_sort(void* arr, int left, int right, size_t size, int (*cmp)(void* a, void* b));

