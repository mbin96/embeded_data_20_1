#include <stdio.h>

#define MAX 10
int stack[MAX];
int top;

//
void init_stack(void);
int push(int t);
int pop();
//

//function
void init_stack(void)
{
    top = -1;
}

int push(int t)
{
    if (top >= MAX - 1)
    {
        printf("Stack overflow !!!\n");
        return -1;
    }
    stack[++top] = t;
    return t;
}

int pop()
{
    if (top < 0)
    {
        printf("Stack underflow !!!\n");
        return -1;
    }
    return stack[top--];
}

//print stack top to bottom
void printStack(){
    int iter = top;
    printf("====print stack====\n");
    while(iter >= 0){
        printf("%d\n",stack[iter]);
        iter--;
    }
    printf("====print stack====\n");
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
    init_stack();
    pop();
}
