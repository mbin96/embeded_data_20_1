#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rbtree.h"
node * initTree(node ** head){
    *head = (node *)malloc(sizeof(node));
    (*head)->right = NULL;
    (*head)->left = NULL;
    (*head)->red = 0;
}

void printTree(node * base, size_t * num, void print (void *a)){
    if (base == NULL || num == 0){
        return;
    }
    printTree(base->left, num, print);
    if (base->red){
        printf("r - ");
    }else{
        printf("b - ");
    }
    print(base+1);
    (*num)--;
    printTree(base->right, num, print);
}

node *rotate(void * key, node *pivot, node *base,FCMP fcmp)
{
    node *child, *gchild;
    if (fcmp(key, pivot+1) < 0 || pivot == head)
        child = pivot->left;
    else
        child = pivot->right;
    if (fcmp(key, child+1) < 0)
    { 
        // L rotation
        gchild = child->left;
        child->left = gchild->right;
        gchild->right = child;
    }
    else
    {
        // R rotation
        gchild = child->right;
        child->right = gchild->left;
        gchild->left = child;
    }
    if (fcmp(key, pivot+1) < 0|| pivot == base)
        pivot->left = gchild;
    else
        pivot->right = gchild;
    return gchild;
}

node *rbti_insert(void * key, node *base, size_t width,size_t *num,FCMP fcmp)
{
    node *t, *parent, *gparent, *ggparent;
    ggparent = gparent = parent = base;
    t = base->left;
    while (t != NULL)
    {
        if (fcmp(key, t+1) == 0)
            return NULL;
        //What does it mean ? 
        if (t->left && t->right && t->left->red && t->right->red)
        {
            //What does it mean ? 
            t->red = 1;
            t->left->red = t->right->red = 0;
                //Rotation is required 
            if (parent->red)
            {
                gparent->red = 1;
                //    LR or RL
                 if ((fcmp(key, gparent+1) <0) != (fcmp(key, parent+1) <0))
                    parent = rotate(key, gparent, base,fcmp);
                t = rotate(key, ggparent, base,fcmp);
                t->red = 0;
            }
            base->left->red = 0;
        }
        ggparent = gparent;
        gparent = parent;
        parent = t;
        if (fcmp(key, t+1) < 0)
            t = t->left;
        else
            t = t->right;
    }
    t = (node *)malloc(sizeof(node) + width);

    t->left = NULL;
    t->right = NULL;
    memcpy(t+1, key, width);
    if (fcmp(key, parent+1) <0 || parent == base)
        parent->left = t;
    else
        parent->right = t;
    (*num)++;
    t->red = 1;
    if (parent->red)
    {
        gparent->red = 1;
        if ((fcmp(key, gparent+1) <0) != (fcmp(key, parent+1) <0))
            parent = rotate(key, gparent, base,fcmp);
        t = rotate(key, ggparent, base,fcmp);
        t->red = 0;
    }
    base->left->red = 0;
    size_t treeSize = num;
    printTree(head -> left, &treeSize, print_wcount);
    return t;
}
