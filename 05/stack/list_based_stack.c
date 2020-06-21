#include <stdio.h>
#include <stdlib.h>

typedef struct _node
{
    int key;
    struct _node *next;
} node;
//(globally defined)
node *head, *tail;

void init_stack()
{
    head = (node *)calloc(1, sizeof(node));
    tail = (node *)calloc(1, sizeof(node));
    head->next = tail;
    tail->next = tail;
}

int push(int k)
{
    node *t;
    if ((t = (node *)malloc(sizeof(node))) == NULL)
    {
        printf("Out of memory !\n");
        return -1;
    }
    t->key = k;
    t->next = head->next;
    head->next = t;
    return k;
}

int pop()
{
    node *t;
    int k;
    if (head->next == tail)
    {
        printf("Stack underflow !\n");
        return -1;
    }
    t = head->next;
    k = t->key;
    head->next = t->next;
        free(t);
    return k;
}

void clear()
{
    node *t, *s;
    t = head -> next;
    while (t != tail)
    {
        //현재껏
        s = t;
        //다음것
        t = t->next;
        free(s);
    }

    head->next = tail;
}

void printStack()
{
    node *t;
    t = head->next;
    while (t != tail)
    {
        printf("%-6d", t->key);
        t = t->next;
    }
    printf("\n");
}


int main(){
    int k;
    init_stack();
    push(3);
    push(6);
    push(9);
    push(1);
    push(6);
    push(3);

    printStack();

    pop();

    printStack();

    push(4);
    push(8);
    push(7);
    push(2);
    push(0);

    push(2);

    printStack();
    init_stack();
    pop();

}