#include <stdlib.h>
#include "llist.h"

llist* create_llist(){
    llist* list = (llist*)malloc(sizeof(llist));
    if (!list) return NULL;
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}
    
void delete_llist(llist* list, void (*llist_n_removal) (llist_n* node)){
    llist_n* ptr = list->head;
    while (ptr){
        llist_n* next = ptr->next;
        if (llist_n_removal) // if a node removal function is passed, call it
            llist_n_removal(ptr);
        else 
            llist_n_clean(ptr); // otherwise, unlink the node
        ptr = next;
    }
    free(list);
}

void llist_n_clean(llist_n* node){
    if (!node) return;
    node->next = NULL;
    node->prev = NULL;
}

void llist_append(llist* list, llist_n* node){
    if (!list || !node) return;
    llist_n_clean(node);
    if (list->size == 0){
        list->head = node;
        list->tail = node;
    } else {
        list->tail->next = node;
        node->prev = list->tail;
        list->tail = node;
    }
    list->size++;
}

void llist_prepend(llist* list, llist_n* node){
    if (!list || !node) return;
    llist_n_clean(node);
    if (list->size == 0){
        list->head = node;
        list->tail = node;
    } else {
        node->next = list->head;
        list->head->prev = node;
        list->head = node;
    }
    list->size++;
}

llist_n* llist_get(llist* list, int n){
    if (!list) return NULL;
    if (n >= list->size || n < 0) return NULL;

    llist_n* ptr = list->head;
    int i = 0;
    while (ptr && (i < n)){
        ptr = ptr->next;
        i++;
    }
    return ptr;
} 

int llist_size(llist* list){
    if (list) return list->size;
    return 0;
}

void llist_insert(llist* list, llist_n* node, int n){
    if (!list || !node) return;
    llist_n_clean(node);
    if (n >= list->size){
        llist_append(list, node);
        return;
    }
    if (n <= 0){
        llist_prepend(list, node);
        return;
    }
    llist_n* ptr = llist_get(list, n);
    node->next = ptr;
    node->prev = ptr->prev;
    node->prev->next = node;
    ptr->prev = node;
    list->size++;
    return;
}

void llist_remove(llist* list, int n, void (*llist_n_removal) (llist_n* node)){
    if (!list) return;
    llist_n* ptr = llist_get(list, n);
    if (!ptr) return;

    if (ptr->prev) ptr->prev->next = ptr->next;
    else list->head = ptr->next;

    if (ptr->next) ptr->next->prev = ptr->prev;
    else list->tail = ptr->prev;

    if (llist_n_removal) llist_n_removal(ptr);
    else llist_n_clean(ptr); 

    list->size--;
    return;
}

void llist_replace(llist* list, llist_n* node, int n, void (*llist_n_removal) (llist_n* node)){
    if (!list) return;
    llist_n* ptr = llist_get(list, n);
    if (!ptr) return;
    llist_n_clean(node);

    node->next = ptr->next;
    node->prev = ptr->prev;

    if (node->next) node->next->prev = node;
    else list->tail = node;

    if (node->prev) node->prev->next = node;
    else list->head = node;

    if (llist_n_removal)
        llist_n_removal(ptr);
    else
        llist_n_clean(ptr); 
    return;
}

void llist_swap(llist* list, int n, int m){
    if (!list || n == m) return;
    if (m < n){ // ensure node1 is always the first
        int t = m;
        m = n;
        n = t;
    }
    
    llist_n* node1 = llist_get(list, n);
    llist_n* node2 = llist_get(list, m);
    if (!node1 || !node2) return;

    llist_n* n1_prev = node1->prev;
    llist_n* n1_next = node1->next;
    llist_n* n2_prev = node2->prev;
    llist_n* n2_next = node2->next;

    if (m - n == 1){ // if they are right next to eachother
        node1->next = n2_next;
        node1->prev = node2;
        node2->next = node1;
        node2->prev = n1_prev;
    } else {
        node1->next = n2_next;
        node1->prev = n2_prev;
        node2->next = n1_next;
        node2->prev = n1_prev;
    }

    if (node1->next) node1->next->prev = node1;
    else list->tail = node1;

    if (node1->prev) node1->prev->next = node1;
    else list->head = node1;

    if (node2->next) node2->next->prev = node2;
    else list->tail = node2;

    if (node2->prev) node2->prev->next = node2;
    else list->head = node2;

    return;
}

llist* llist_split(llist* list, int n){
    if (!list) return NULL;
    llist_n* ptr = llist_get(list, n);
    if (!ptr) return (NULL);
    llist* new = create_llist();
    if (!new) return (NULL);

    new->size = list->size - n;
    new->head = ptr;
    new->tail = list->tail;

    list->tail = ptr->prev;
    if (list->tail)
        list->tail->next = NULL;
    else // list is now empty
        list->head = NULL;

    new->head->prev = NULL; // sever last connection

    list->size = n;
    return new;
}

void llist_concatenate(llist* aug, llist* add){
    if (!aug || !add) return;
    if (add->size == 0) return;
    if (aug->size == 0){
        aug->head = add->head;
        aug->tail = add->tail;
        aug->size = add->size;
    } else {
       aug->tail->next = add->head;
       add->head->prev = aug->tail;
       aug->tail = add->tail;
       aug->size += add->size;
    }
    add->head = NULL;
    add->tail = NULL;
    add->size = 0;
    return;
}

void llist_rotate(llist* list, int n){
    if (!list) return;
    if (list->size == 0 || list->size == 1) return;

    n = n % list->size;
    if (n < 0) {
        n += list->size;
    }
    if (n == 0) return;

    list->head->prev = list->tail;
    list->tail->next = list->head;
    llist_n* ptr = list->head;

    for (int i = 0; i < n; i ++) {
       ptr = ptr->next; 
    }
    
    list->tail = ptr->prev;
    list->tail->next = NULL;
    list->head = ptr;
    list->head->prev = NULL;
    return;
}
