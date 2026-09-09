#include <string.h>
#include <stdlib.h>
#include "insertion_sort.h"

void insertion_sort(void* arr, int left, int right, size_t size, int (*cmp) (void* a, void* b)){
    for (int i = left + 1; i < right; i++) {
        char temp[size];
        memcpy(temp, (char*)arr + (i * size), size); // store the value of the element
        int j = i - 1;
        while (j >= 0 && cmp(temp, (char*)arr + (j * size)) < 0){ // while values are more than the stored, move them over
            memcpy((char*)arr + ((j + 1) * size), (char*)arr + (j * size), size);
            j--; // then check previous element 
        }
        memcpy((char*)arr + ((j + 1) * size), temp, size); // insertion part
    }
}
