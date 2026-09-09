#pragma once
#include <stddef.h>
#include <stdlib.h>
#include "../helper/container.h"

/* a quick note about this struct and how it works
 * first we create an alias for "struct llist_n" and call it just llist_n
 * then we define this struct. but how can we use the struct within itself if its not defined??
 * this is because they are only pointers! of which all pointers are 8 bytes
 * because of this it knows how big to make the struct, so we don't get any problems */
typedef struct llist_n llist_n;
struct llist_n{
    llist_n* next;
    llist_n* prev;
};

typedef struct llist llist;
struct llist{
    llist_n* head;
    llist_n* tail;
    int size;
};

// create a new llist
llist* create_llist();

// unlink all nodes, pass in removal function if data needs to be altered / freed when removed
void delete_llist(llist* list, void (*llist_n_removal) (llist_n* node));

// helper function to remove links in nodes
void llist_n_clean(llist_n* node);

// append llist_n to llist
void llist_append(llist* list, llist_n* node);

// prepend llist_n to llist
void llist_prepend(llist* list, llist_n* node);

// get a pointer to the llist_n in the nth position
llist_n* llist_get(llist* list, int n);

// size of llist; # of llist_n in llist
int llist_size(llist* list);

// insert into llist a llist_n at nth position
void llist_insert(llist* list, llist_n* node, int n);

// remove llist_n at nth position in llist, pass in removal function if data needs to be altered / freed when removed
void llist_remove(llist* list, int n, void (*llist_n_removal) (llist_n* node));

// replace llist_n at nth position in llist with another, pass in removal function if data needs to be altered / freed when removed
void llist_replace(llist* list, llist_n* node, int n, void (*llist_n_removal) (llist_n* node));

// swap the llist_n in the nth and mth positions in the llist
void llist_swap(llist* list, int n, int m);

// split llist into two, the second starting at the nth position in the original
llist* llist_split(llist* list, int n);

// append add to aug, afterwards add will be empty
void llist_concatenate(llist* aug, llist* add);

// rotate llist by n nodes
void llist_rotate(llist* list, int n);

