/* a set of macros to help easily build dynamic arrays. 
 * use the declare_darray_struct macro to declare a dynamic array struct, that contains elements of type DATATYPE
 * the macros have bounds checks for insert and remove, but not for get and set.
 * multiline macros are wrapped in do while loops that execute once, so they can be put into blockless if statements, for, and while loops*/

#pragma once
#include <stdio.h>
#include <stdlib.h>

// macro for declaring dynamic array structs, named STRUCT_NAME that holds elements of DATATYPE
// also creates an static inline creation function for that struct, called create_STRUCT_NAME
#define declare_darray_struct(DATATYPE, STRUCT_NAME) \
    typedef struct { \
        int max; /* allocated space for the array */ \
        int size; /* current number of elements */ \
        DATATYPE* elements; /* the array */ \
        int elem_size; /* the size in bytes of DATATYPE, used for realloc calls */ \
    } STRUCT_NAME; \
    static inline STRUCT_NAME* create_##STRUCT_NAME(int num_elements) { \
        STRUCT_NAME* darr = (STRUCT_NAME*)malloc(sizeof(STRUCT_NAME)); \
        if (!darr) return NULL; \
        darr->max = num_elements; \
        darr->size = 0; \
        darr->elem_size = sizeof(DATATYPE); \
        darr->elements = (DATATYPE*)malloc(sizeof(DATATYPE) * num_elements); \
        return darr; \
    }

// free darray and its elements
#define delete_darray(NAME) \
    do { \
        free((NAME)->elements); \
        free(NAME); \
    } while (0)

// copy elements from SRC to DEST. DEST must be an existing darray.
// The arguments may use different darray structs but cant have different element types
#define darray_copy(SRC, DEST) \
    do { \
        if ((SRC)->size > (DEST)->max) { \
            (DEST)->max = (SRC)->size; \
            (DEST)->elements = realloc((DEST)->elements, (DEST)->elem_size * (DEST)->max); \
        } \
        for (int i = 0; i < (SRC)->size; i++) { \
            (DEST)->elements[i] = (SRC)->elements[i]; \
        } \
        (DEST)->size = (SRC)->size; \
    } while (0)

// get value from darray NAME at INDEX
#define darray_get(NAME, INDEX) ((NAME)->elements[INDEX])

// set value from darray NAME at INDEX to VALUE
#define darray_set(NAME, INDEX, VALUE) ((NAME)->elements[INDEX] = (VALUE))

// set all elements in darray NAME to VALUE
#define darray_set_all(NAME, VALUE) \
    do { \
        for (int i = 0; i < (NAME)->size; i++) { \
            (NAME)->elements[i] = (VALUE); \
        } \
    } while (0)

// size of the darray
#define darray_size(NAME) ((NAME)->size)

// is zero if darray is empty
#define darray_empty(NAME) ((NAME)->size == 0)

// if an added element would exceed the bounds of the array, reallocate the array
#define resize_darray_if_needed(NAME) \
    do { \
        if ((NAME)->size + 1 > (NAME)->max) { \
            (NAME)->max = ((NAME)->max == 0) ? 1 : (NAME)->max * 2; \
            (NAME)->elements = realloc((NAME)->elements, (NAME)->max * (NAME)->elem_size); \
        } \
    } while (0)

// add VALUE to the back of darray NAME
#define darray_push_back(NAME, VALUE) \
    do { \
        resize_darray_if_needed(NAME); \
        (NAME)->elements[(NAME)->size] = (VALUE); \
        (NAME)->size++; \
    } while (0)

// remove the element at the back of darray NAME
#define darray_pop_back(NAME) \
    do { \
        if ((NAME)->size > 0) { \
            (NAME)->size--; \
        } \
    } while (0)

// insert VALUE into position INDEX of darray NAME
#define darray_insert(NAME, VALUE, INDEX) \
    do { \
        if ((INDEX) >= 0) { /* don't insert at negative indices */ \
            resize_darray_if_needed(NAME); \
            if ((INDEX) >= (NAME)->size) { /* if the index exceeds the size, append to the end */ \
                (NAME)->elements[(NAME)->size] = (VALUE); \
                (NAME)->size++; \
            } else { /* otherwise, move over all elements after INDEX, inclusive, then insert VALUE at INDEX */ \
                for (int i = (NAME)->size; i > (INDEX); i--) { \
                    (NAME)->elements[i] = (NAME)->elements[i - 1]; \
                } \
                (NAME)->elements[INDEX] = (VALUE); \
                (NAME)->size++; \
            } \
        } \
    } while (0)

// remove the value at INDEX from darray NAME
#define darray_remove(NAME, INDEX) \
    do { \
        if ((INDEX) >= 0 && (INDEX) < (NAME)->size && (NAME)->size != 0) { /* bounds and empty array check */ \
            for (int i = (INDEX); i < (NAME)->size - 1; i++) { \
                (NAME)->elements[i] = (NAME)->elements[i + 1]; \
            } \
            (NAME)->size--; \
        } \
    } while (0)
