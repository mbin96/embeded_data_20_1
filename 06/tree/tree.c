#include <stdio.h> 
#include <stdlib.h>
#define MAX 100


typedef struct _node
{
    int key;
    struct _node *left;
    struct _node *right;
} node;

node *head, *tail;
node *stack[MAX];
node *queue[MAX];

int top, front, rear;

//stack and quque
void init_stack() { top = -1; }
void init_queue() { front = rear = 0; }
int is_stack_empty() { return (top == -1); }
int is_queue_empty() { return (front == rear); }

node *push(node *t)
{
    stack[++top] = t;
    return t;
}

node *pop() { return stack[top--]; }

node *put(node *t)
{
    queue[rear] = t;
    rear = ++rear % MAX;
    return t;
}

node *get()
{
    node *t;
    t = queue[front];
    front = ++front % MAX;
    return t;
}

void init_tree()
{
    head = (node *)calloc(1, sizeof(node));
    tail = (node *)calloc(1, sizeof(node));
    head->left = tail;
    head->right = tail;
    tail->left = tail;
    tail->right = tail;
}


void visit(node *t) { printf("% c ", t->key); }

//tree
//왼쪽부터 탐색
void preorder_traverse(node *t)
{
    if (t != tail)
    {
        visit(t);
        preorder_traverse(t->left);
        preorder_traverse(t->right);
    }
}

void inorder_traverse(node *t)
{
    if (t != tail)
    {
        inorder_traverse(t->left);
        visit(t);
        inorder_traverse(t->right);
    }
}

void levelorder_traverse(node *t)
{
    put(t);
    while (!is_queue_empty())
    {
        t = get();
        visit(t);
        if (t->left != tail)
            put(t->left);
        if (t->right != tail)
            put(t->right);
    }
}

int is_operator(int k) { return (k == '+' || k == '-' || k == '*' || k == '/'); }


node *make_parse_tree(char *p)
{
    node *t;
    while (*p!='\0')
    {
        while (*p == ' ')
            p++;
        t = (node *)calloc(1, sizeof(node));
        printf("%c\n",*p);
        t->key = *p;
        t->left = tail;
        t->right = tail;
        if (is_operator(*p))
        {
            printf("is op\n",*p);
            t->right = pop();
            t->left = pop();
        }
        push(t);
        p++;
    }
    return pop();
}

void main()
{
    // char post[256];
    char * post = "A B + C D - * E / F G * +";

    init_stack();
    init_queue();
    init_tree();
    
    // while (1)
    // {
    // printf("\n\nInput postfix expression > ");
    // gets(post);
    // if (*post == NULL)
    //     break;
    head->right = make_parse_tree(post);
    printf("\nPre - order traverse >");
    preorder_traverse(head->right);
    // }
}