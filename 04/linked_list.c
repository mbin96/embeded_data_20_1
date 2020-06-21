#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"


void printList(){
    node *temp;
    temp = head->next;

    printf("+++print list+++\n");
    
    //계속해서 다음꺼로
    for (int i = 1; temp != tail; i++){
        printf("%dth node : %d\n",i,temp->key);
        temp = temp->next;
    }
    printf("+++end of list+++\n");
    
}

void initList()
{
    head = (node *)calloc(1, sizeof(node));
    tail = (node *)calloc(1, sizeof(node));
    head->next = tail;
    tail->next = tail;
}

//insert new node fo key after node *t
node *insertAfter(int key, node *t)
{
    node *temp;
    temp = (node *)calloc(1, sizeof(node));

    temp->key = key;
    temp->next = t->next;
    t->next = temp;

    return temp;
}

//delete next node of key node
int deleteNext(node *t)
{
    node *temp;
    if (t->next == tail)
        return 0;
    temp = t->next;

    //다다음꺼 연결하고 지움
    t->next = t->next->next;
    free(temp);
    return 1;
}


node *findNode(int key)
{
    node *temp;
    temp = head->next;
    //계속해서 다음꺼로
    int iter = 1;
    while (temp->key != key && temp != tail){
        temp = temp->next;
        iter++;
    }
    if(temp != tail)
        printf("find %dth node\n",iter);
    else
    {
        printf("can't find node");
    }
    
    return temp;
}

//delete node
int deleteNode(int key)
{
    node *s, *p;
    //primary
    p = head;
    //secondary
    s = p->next;

    while (s->key != key && s != tail)
    {
        p = p->next;
        s = p->next;
    }
    //찾았으면?
    if (s != tail)
    {
        p->next = s->next;
        free(s);
        return 1;
    }
    else
    //지우기 실패
        return 0;
}

//insert with ordering(integer)
node *orderedInsert(unsigned int key)
{
    //node 선언 secondary, primary, real?(tmp)
    node *s, *p, *r;
    p = head;
    s = p->next;
    while (s->key <= key && s != tail)
    {
        p = p->next;
        s = p->next;
    }
    
    r = (node *)calloc(1, sizeof(node));
    r->key = key;
    p->next = r;
    r->next = s;
    return r;
}

node *deleteAll()
{
    node *s;
    node *t;
    t = head->next;
    while (t != tail)
    {
        s = t;
        t = t->next;
        free(s);
    }
    head->next = tail;
    return head;
}
