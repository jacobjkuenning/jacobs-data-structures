/* Place to put frequently used macros */
#pragma once
#include <stddef.h>
#include <stdlib.h>

// finds the pointer to struct STRUCT_NAME that contains NODE_PTR as MEMBER
#define container_of(NODE_PTR, STRUCT_NAME, MEMBER)\
    (STRUCT_NAME*)((char*)NODE_PTR - offsetof(STRUCT_NAME, MEMBER))

// swaps the elements at indices A and B in dynamic array DARR, with elements sized SIZE
#define memswap(DARR, A, B, SIZE)\
    do {\
        char temp[SIZE];\
        memcpy(temp, (char*)DARR + (A * SIZE), SIZE);\
        memcpy((char*)DARR + (A * SIZE), (char*)DARR + (B * SIZE), SIZE);\
        memcpy((char*)DARR + (B * SIZE), temp, SIZE);\
    } while (0);

