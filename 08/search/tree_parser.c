#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bts_library.h"
#include "graphics.h"


#define  NODE  1

#define  LINK   2

#define  TAIL    4

#define  DY      50


typedef struct _wcount{
    int count;
    char word[20]; //store word
}wcount;

void _draw_node(node *p, void (*fptr)(void *, char *), int x1, int x2, int y, int mode)
{
    char content[20];
    if (p != NULL)
    {
        _draw_node(p->left, fptr, x1, (x1 + x2) / 2, y + DY, mode);
        fptr(p->key, content);
        fillellipse((x1 + x2) / 2, y, textwidth(content) / 2 + 5, textheight(content) / 2 + 5);
        outtextxy((x1 + x2) / 2, y, content);
        _draw_node(p->right, fptr, (x1 + x2) / 2, x2, y + DY, mode);
    }
    else if (mode & TAIL)
        fillellipse((x1 + x2) / 2, y, 3, 3);
}
void _draw_link(node *p, int x1, int x2, int y, int mode)
{
    if (p != NULL)
    {
        lineto((x1 + x2) / 2, y);
        _draw_link(p->left, x1, (x1 + x2) / 2, y + DY, mode);
        moveto((x1 + x2) / 2, y);
        _draw_link(p->right, (x1 + x2) / 2, x2, y + DY, mode);
        lineto((x1 + x2) / 2, y);
    }
    else if (mode & TAIL)
    {
        lineto((x1 + x2) / 2, y);
        moveto((x1 + x2) / 2, y);
    }
}


void btv_draw(node *p, void (*fptr)(void *, char *), int mode)
{
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");
    settextjustify(CENTER_TEXT, CENTER_TEXT);
    setfillstyle(0, BLACK);
    moveto(getmaxx() / 2, 10);
    if (mode & LINK)
        _draw_link(p, 5, getmaxx() - 5, 10, mode);
    if (mode & NODE)
        _draw_node(p, fptr, 5, getmaxx() - 5, 10, mode);
}

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

node *head;
char delim[] = " \t\r\n,.-";
#define SIZE 12
int main(){
    // char s[] = "All the things you are";
    // char *token;
    
    // token = strtok(s, delim);
    // while(token != NULL){
    //     printf("%s\n",token);
    //     token = strtok(NULL, delim);
    // }

    int i, num = 0, cnt = 0;
    char *tok;
    char str[256];
    wcount wc, *wcp;
    init_tree(&head);
    FILE *fp;
    fp = fopen("test.txt", "r");

    printf("1");
    fgets(str, 256, fp); // read one line
    
    while (!feof(fp)){
        tok = strtok(str, delim);
        while (tok){
            // printf("%s\n",tok);
            strcpy(wc.word, tok);
            // printf("%s\n",tok);
            wcp = (wcount *)bti_search(&wc, head, &num, sizeof(wcount), wcount_cmp);
            // printf("%s\n",tok);
            if (wcp == NULL) {
                wc.count = 1; // count frequency
                bti_insert(&wc, head, &num, sizeof(wcount), wcount_cmp);
            }else
                (wcp->count)++;
            tok = strtok(NULL, delim);
        }
        fgets(str, 256, fp);
    }
    printf("\n");
    bti_list((head->left), print_wcount);
    btv_draw(head->left, make_str, LINK | NODE | TAIL);
    
    printf("\n");
    printf("\n");
    
    // getchar();
    btv_balance(head, &num, sizeof(wcount));
    bti_list((head->left), print_wcount);
    btv_draw(head->left, make_str, LINK | NODE | TAIL);
    
    getchar();
}