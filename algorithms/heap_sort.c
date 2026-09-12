#include "heap.h"
#include "../helper/utils.h"

void heap_sort(void* arr, int n, size_t size, int(*cmp) (const void* a, const void* b)){
    build_heap(arr, n, size, cmp); // turn array into heap
    for (int i = n - 1; i >= 0; i--) {
        memswap(arr, 0, i, size);
        heapify(arr, 0, i, size, cmp);
    }
}

void build_heap(void* arr, int n, size_t size, int (*cmp) (const void* a, const void* b)){
    for (int i = (size * n) /2 - 1; i >= 0; i--){
        heapify(arr, i, n, size, cmp);
    }
    return;
}

void heapify(void* arr, int i, int n, size_t size, int (*cmp) (const void* a, const void* b)){
    int left = (i*2) + 1; // find index of left and right nodes
    int right = (i*2) + 2;

    int largest = i;
    if (left < n){ // if left node is within bounds
       if (cmp((char*)arr + (left * size), (char*)arr + (i * size)) > 0){ // if left node is larger than its parent
          largest = left;  
       }
    }
    if (right < n){
       if (cmp((char*)arr + (right * size), (char*)arr + (largest * size)) > 0){ // if right node is larger than it's parent
            largest = right;
       }
    }
    if (largest != i){
        memswap(arr, i, largest, size); // swap values of parent and largest child
        heapify(arr, largest, n, size, cmp); // recurse on swapped node
    }
    return;
}


