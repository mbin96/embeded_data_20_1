#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int (*FCMP)(const void *, const void *);

typedef struct _node{
    struct _node * left;
    struct _node * right;
    int red;
    int key;
}node;
extern node * head;


node *rbti_insert(void * key, node *base, size_t width, size_t *num,FCMP fcmp);
node * initTree(node ** head);
void printTree(node * base, size_t * num, void print (void *a));
node *rotate(void * key, node *pivot, node *base,FCMP fcmp);
extern void print_wcount(void *a);