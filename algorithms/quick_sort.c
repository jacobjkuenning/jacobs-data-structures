#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include "quick_sort.h"
#include "../helper/utils.h"

int partition(void* arr, int left, int right, size_t size, int (*cmp)(void* a, void* b)){
    int p = (rand() % (right - left + 1)) + left; // select pivot index
    memswap(arr, p, right, size); // move partition element to the right
    int store = left;
    for (int i = left; i < right; i++) { // compare all numbers from the start to the end with the end
        int compar = cmp((char*)arr + (i * size), (char*)arr + (right * size)); // compare curr element with partioned element
        if (compar <= 0){ // if the element is less than the partitioned element, move to appropriate side
            memswap(arr, i, store, size);
            store++;
        }
    }
    memswap(arr, store, right, size); // put partion element exactly where it goes
    return store;
}

void quick_sort(void* arr, int left, int right, size_t size, int (*cmp)(void* a, void* b)){
    if (left < right){
        int pi = partition(arr, left, right, size, cmp);
        quick_sort(arr, left, pi - 1, size, cmp); // recurse right and left
        quick_sort(arr, pi + 1, right, size, cmp);
    }
}
