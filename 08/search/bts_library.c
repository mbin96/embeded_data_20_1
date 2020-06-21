#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bts_library.h"

void init_tree(node **p){
    *p = (node *)malloc(sizeof(node));
    (*p)->left = NULL;
    (*p)->right = NULL;
}

void bti_list(node *p, void (*fptr)(void *))
{
    // printf("1");
    int i;
    static int x = 0;
    if (p != NULL)
    {
        x += 2; // position for displaying a node
        // a kind of inorder traverse
        bti_list(p->right, fptr);
        for (i = 2; i < x; i++)
            printf(" ");
        fptr(p->key); // print it in the monitor
        
        bti_list(p->left, fptr);
        x -= 2;
    }
}


void *bti_search(void * key, node * base, int * num, int width, FCMP fcmp)
{
    node *s;
    s = base->left; // root node 무조껀 왼쪽에서 시작?
    while (s != NULL && fcmp(key, s->key) != 0)
    {
        if (fcmp(key, s->key) < 0)
            s = s->left;
        //크면 오른쪽
        else
            s = s->right;
    }
    if (s == NULL)
        return NULL;
    else
        return s->key;
}

void *bti_insert(void * key, node * base, int * num, int width, FCMP fcmp)
{
    node *p, *s;
    //부모노드
    p = base;
    //자식노드
    s = base->left;
    //베이스 아래의 트리가 있으면 NULL이 나올때까지 탐색
    while (s != NULL)
    {
        p = s;
        //fst < snd == true
        if (fcmp(key, s->key) < 0)
            s = s->left;
        else
            s = s->right;
    }
    
    void * tmp = malloc(width); 
    s = (node *)malloc(sizeof(node));
    memcpy(tmp, key, width);
    
    s->key = tmp;
    s->left = NULL;
    s->right = NULL;

    if (p == base || fcmp(key, p->key) < 0)
        p->left = s;
    else
        p->right = s;
    (*num)++;
    return s;
}
int _index = 0;
node *_balance(int N, void **a, int width)
{
    int nl, nr;
    node *p;
    if (N > 0)
    {
        nl = (N - 1) / 2;
        nr = N - nl - 1;
        p = (node *)malloc(sizeof(node));
        p->left = _balance(nl, a, _index);
        p->key = a[(_index)++];
        p->right = _balance(nr, a, _index);
        return p;
    }
    else
        return NULL;
}
void _sort(node *p, void **a, int width)
{
    if (p != NULL)
    {
        _sort(p->left, a, width);
        a[(_index)++] = p->key;
        _sort(p->right, a, width);
    }
}
void _deleteall(node *t)
{
    if (t != NULL)
    {
        _deleteall(t->left);
        _deleteall(t->right);
        free(t);
    }
}
void *btv_deleteall(node *base, int *num)
{
    node *t;
    t = base->left;
    _deleteall(t);
    base->left = NULL;
    base->right = NULL;
    *num = 0;
    return base;
}

void btv_balance(node *base, int *num, int width)
{
    void **tmp;
    int ntmp = *num;
    tmp = malloc(width * ntmp);
    _index = 0;
    _sort(base->left, tmp, width);
    ntmp = *num;
    btv_deleteall(base, num);
    _index = 0;
    base->left = _balance(ntmp, tmp, width);
    *num = ntmp;
    free(tmp);
}
