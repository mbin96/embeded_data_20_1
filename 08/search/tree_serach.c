#include <stdio.h>

#include <stdlib.h>

#include <string.h>

typedef struct _node
{
    int key;
    struct _node *left;
    struct _node *right;
} node;


void visit(node *t) { printf("% c ", t->key); }

//tree
//왼쪽부터 탐색
void preorder_traverse(node *t)
{
    if (t != NULL)
    {
        visit(t);
        preorder_traverse(t->left);
        preorder_traverse(t->right);
    }
}

void inorder_traverse(node *t)
{
    if (t != NULL)
    {
        inorder_traverse(t->left);
        visit(t);
        inorder_traverse(t->right);
    }
}


node *bti_search(int key, node *base, int *num)
{
    node *s;
    s = base->left; // root node 무조껀 왼쪽에서 시작?
    while (key != s->key && s != NULL)
    {
        //작으면 왼쪽
        if (key < s->key)
            s = s->left;
        //크면 오른쪽
        else
            s = s->right;
    }
    if (s == NULL)
        return NULL;
    else
        return s;
}

node *bti_insert(int key, node *base, int *num)
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
        if (key < s->key)
            s = s->left;
        else
            s = s->right;
    }
    //
    s = (node *)malloc(sizeof(node));
    s->key = key;
    s->left = NULL;
    s->right = NULL;
    //
    if (key < p->key || p == base)
        p->left = s;
    else
        p->right = s;
    (*num)++;
    return s;
}

node *bti_delete1(int key, node *base, int *num)
{
    node *parent, *son, *del, *nexth;
    parent = base;
    del = base->left;
    //search
    while (key != del->key && del != NULL)
    {
        parent = del;
        if (del->key > key)
            del = del->left;
        else
            del = del->right;
    }
    //key 에 해당값이 없음
    if (del == NULL)
        return NULL;
    //del의 자식이 하나도 없음
    if (del->left == NULL && del->right == NULL)
        son = NULL;
    //del의 자식이 둘 다 있는경우
    else if (del->left != NULL && del->right != NULL)
    {
        //오른쪽 자식을 먼저 넣는다.
        nexth = del->right;
        if (nexth->left != NULL)
        {
            //가장 하위로
            while (nexth->left->left != NULL)
                nexth = nexth->left;
            son = nexth->left;
            nexth->left = son->right;
            son->left = del->left;
            son->right = del->right;
        }
        else
        {
            son = nexth;
            son->left = del->left;
        }
    }
    //del의 자식이 둘 중 하나 있는경우
    //그냥 이어주기만 하면 된다.
    else //Case 2
    {
        if (del->left != NULL)
            son = del->left;
        else
            son = del->right;
    }
    if (key < parent->key || parent == base)
        parent->left = son;
    else
        parent->right = son;
    free(del);
    (*num)--;
    return parent;
}


node *bti_delete(int key, node *base, int *num)
{
    node *parent, *son, *del, *nexth;
    parent = base;
    del = base->left;
    //search
    while (del != NULL && key != del->key)
    {
        parent = del;
        if (del->key > key)
            del = del->left;
        else
            del = del->right;
    }
    //key 에 해당값이 없음
    if (del == NULL)
        return NULL;
    //del의 자식이 하나도 없음
    if (del->left == NULL && del->right == NULL)
        son = NULL;
    
    /* same with bti_delete1() for finding del node */
    if (del->right == NULL)
        son = del->left;
    else if (del->right->left == NULL)
    {
        son = del->right;
        son->left = del->left;
    }
    else
    {
        nexth = del->right;
        while (nexth->left->left != NULL)
            nexth = nexth->left;
        son = nexth->left;
        nexth->left = son->right;
        son->left = del->left;
        son->right = del->right;
    }
    if (key < parent->key || parent == base)
        parent->left = son;
    else
        parent->right = son;
    free(del);
    (*num)--;
    return parent;
    /* same with bti_delete1() for making connections with new parent */
}

void bti_sort(node *p, int *a, int *index)
{
    if (p != NULL)
    {
        bti_sort(p->left, a, index);
        a[(*index)++] = p->key;
        bti_sort(p->right, a, index);
    }
}

node *_balance(int N, int *a, int *index)
{
    int nl, nr;
    node *p;
    if (N > 0)
    {
        nl = (N - 1) / 2;
        nr = N - nl - 1;
        p = (node *)malloc(sizeof(node));
        p->left = _balance(nl, a, index);
        p->key = a[(*index)++];
        p->right = _balance(nr, a, index);
        return p;
    }
    else
        return NULL;
}

#define SIZE 12
int main(){

    char * input  = "FBOADLCGMHNK";
    node * base = (node*)malloc(sizeof(node));
    int num=0;
    
    //initialize

    for(int i = 0; input[i] != NULL; i++){
        bti_insert(input[i] , base, &num);
    }


    printf("preorder_traverse > ");
    preorder_traverse(base->left);
    printf("\n");

    printf("inorder_traverse >  ");
    inorder_traverse(base->left);

    printf("\n");
    printf("====sortedTree==== \n");

    num=0;
    int sort[SIZE];
    bti_sort(base->left,sort,&num);
    num=0;
    base->left = _balance(SIZE,sort,&num);

    
    // bti_delete('L' , base, &num);
    
    printf("preorder_traverse > ");
    preorder_traverse(base->left);
    printf("\n");
 
    printf("inorder_traverse >  ");
    inorder_traverse(base->left);

    printf("\n");
 
    printf("search 'K' > %p, %c ",bti_search('K' , base, &num),bti_search('K' , base, &num)->key);
    

    return 0;
}