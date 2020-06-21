#include <stdio.h>
#include <stdlib.h>
#include "stack.h"




void calc(char *input, char *output){
    
    int iter = 0;

    while (input[iter]!='\0'){
        switch(input[iter]){
        case '/':
            push((int)'/');
            break;
        case '*':
            push((int)'*');
            break;
        case '+':
            push((int)'+');
            break;
        case '-':
            push((int)'-');
            break;
        case '(': //do nothing
            break;
        case ')':
            *output++ = (char)pop();
            *output++ = ' ';
            // printf("%c",(char)pop());
            break;
        default :
            *output++ = input[iter];
            while(input[iter+1] >= '0' && input[iter+1] <= '9'){
                *output++ = input[++iter];
            }
            *output++ = ' ';
            // printf("%c",input[iter]);
            break;
        }
        iter++;
    }
    *output = '\0';

}

int main(){
    init_stack();

    char calcInput[50];
    char calcOutput[50];
    scanf("%s",calcInput);
    for(int i = 0; calcInput[i]!='\0'; i++){
        printf("%c\n",calcInput[i]);
    }
    calc(calcInput,calcOutput);
    printf("%s",calcOutput);

}