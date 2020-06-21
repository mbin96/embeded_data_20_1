
#ifndef STACK

#define STACK

typedef struct _node
{
    int key;
    struct _node *next;
} node;
//(globally defined)
node *head, *tail;
void printStack();
void clear();
int pop();
int push(int k);
void init_stack();

#endif