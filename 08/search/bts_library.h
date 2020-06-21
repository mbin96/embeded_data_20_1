#ifndef bts_lib
#define bts_lib

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int (*FCMP)(const void *, const void *);

typedef struct _node
{
    void * key;
    struct _node *left;
    struct _node *right;
} node;
int intcmp(const void *a, const void *b);

void init_tree(node **p);
void *bti_insert(void * key, node * base, int * num, int width, FCMP fcmp);
void *bti_search(void * key, node * base, int * num, int width, FCMP fcmp);

void bti_list(node *p, void (*fptr)(void *));
void btv_balance(node *base, int *num, int width);

#endif