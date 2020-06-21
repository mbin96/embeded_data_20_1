#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

int get_stack_top()
{
    if (head->next == tail){
        return -1;
    }
    else{
        return head->next->key;
    }
}
int is_stack_empty(){
    if (head->next == tail){
        return 1;
    }
    else{
        return 0;
    }
}


int is_op(int k)
{
    return (k == '+' || k == '-' || k == '*' || k == '/');
}
int precedence(int op)
{
    if (op == '(')
        return 0;
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    else
        return 3;
}

void postfix(char *dst, char *src)
{
    char c;
    init_stack();
    while (*src != '\0')
    {
        if (*src == '(')
        {
            push(*src);
            src++;
        }
        else if (*src == ')')
        {
            while (get_stack_top() != '(')
            {
                *dst++ = pop();
                *dst++ = ' ';
            }
            //discard '('
            pop();

            src++;
        }
        else if (is_op(*src))
        {
            while ((!is_stack_empty()) && precedence(get_stack_top()) >= precedence(*src))
            {
                *dst++ = pop();
                *dst++ = ' ';
            }
            push(*src);
            src++;
        }
        else if (*src >= '0' && *src <= '9')
        {
            do
            {
                *dst++ = *src++;
            } while (*src >= '0' && *src <= '9');
            *dst++ = ' ';
        }
        else
            src++;
    }
    while (!is_stack_empty())
    {
        *dst++ = pop();
        *dst++ = ' ';
    }
    dst--;
    *dst = '\0';
}


int main()
{
    init_stack();

    // char calcInput[50];
    char calcOutput[50];

    char * calcInput = "(1*(2+3/4)+5)/6+7";
    // scanf("%s", calcInput);
    // for (int i = 0; calcInput[i] != '\0'; i++)
    // {
    //     printf("%c\n", calcInput[i]);
    // }
    postfix(calcOutput,calcInput);
    printf("%s", calcOutput);
}