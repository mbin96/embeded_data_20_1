#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rbtree.h"

typedef struct _wcount{
    int count;
    char word[20]; //store word
}wcount;


node * head;
void make_str(void *a, char *s)
{
    strcpy(s, ((wcount *)a)->word);
}
int wcount_cmp(const void *a, const void *b)
{
    return strcmp(((wcount *)a)->word, ((wcount *)b)->word);
}

void print_wcount(void *a)
{
    printf("%s : %d\n", ((wcount *)a)->word, ((wcount *)a)->count);
}

int main(){
    //init
    initTree(&head);
    size_t treeSize=0;
    char input[] = "you did a good job";

    char *tok;
    wcount wc, *wcp;
    char delim[] = " \t\r\n,.-";
    tok = strtok(input, delim);
    
    while (tok){
        printf("input : %s\n",tok);
        strcpy(wc.word, tok);
        wc.count = 1; // count frequency
        rbti_insert(&wc, head, sizeof(wc),&treeSize,wcount_cmp);
        tok = strtok(NULL, delim);
    }
    printf("\n==result==\n");
    printTree(head -> left, &treeSize,print_wcount);
    // printf("%d ", 1);
}


