#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _node
{
    struct _node *next;
} node;

typedef int (*FCMP)(const void *, const void *);
#define BASE(i) ((char *)base + (i)*width)

int intcmp(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}



void init_list(node **p)
{
    *p = (node *)malloc(sizeof(node));
    (*p)->next = NULL;
}

node *llv_insert(void *key, node *base, size_t *num, size_t width, FCMP fcmp)
{
    node *t;
    t = (node *)malloc(sizeof(node) + width);
    memcpy(t+1,key,width);
    t->next =base->next;
    base->next =t;
    (*num)++;
    return t;
}
void *llv_search(void *key, node *base, size_t *num, size_t width, FCMP fcmp)
{
    node *t;
    t =  base->next;
    while (fcmp(t + 1, key) != 0 && t != NULL)
        t = t->next;
    return (t == NULL ? NULL : t + 1);//들은 주소 리턴
}

#define LEN 5
void main(){
    void *p;
    node *t, *head;
    int size = 0, key = 9;
    int data[LEN] = { 3, 1, 9, 7, 5};
    init_list(&t); // using the pointer t
    
// Construct your linked list
// Print out your linked list using for loop and printf()
    head = t;
    for(int i = 0;i <LEN;i++){
        p = llv_insert(&data[i],head,&size,sizeof(int),intcmp);
        printf("%d\n",*((int *)((node *)p+1)));
    }

// Conduct search with key value
    p = llv_search(&key,head,&size,sizeof(int),intcmp);
    printf("%d 를 %p에서 찾았음\n",*((int *)(p)),(int *)(p));

    int position;
    t = head->next;
// Print out the relative position of key value to the starting addr. of LL

    for(int i = 0;i <LEN;i++){
        if(*(int*)(t+1) == 5){
            printf("%d th position(zerobase)",i);
            break;
        }
        t = t -> next;
    }

}
