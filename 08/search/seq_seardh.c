#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef int (*FCMP)(const void *, const void *);
#define BASE(i) ((char *)base + (i)*width)

int intcmp(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

int lv_search(void *key, void *base, size_t *num, size_t width, FCMP fcmp);
int lv_insert(void *key, void *base, size_t *num, size_t width, FCMP fcmp);
int lv_delete(void *key, void *base, size_t *num, size_t width, FCMP fcmp);
int lfv_search(void *key, void *base, size_t *num, size_t width, FCMP fcmp);
int lv_search(void *key, void *base, size_t *num, size_t width, FCMP fcmp)
{
    int i = 0;
    while (fcmp(BASE(i), key) != 0 && i < *num)
        i++;
    return (i < *num ? i : -1);
}
int lv_insert(void *key, void *base, size_t *num, size_t width, FCMP fcmp)
{
    memcpy(BASE((*num++)), key, width);
    return *num - 1;
}
int lv_delete(void *key, void *base, size_t *num, size_t width, FCMP fcmp)
{
    int p, i;
    if (*num > 0)
    {
        if ((p = lv_search(key, base, num, width, fcmp)) < 0)
            return -1;
        for (i = p + 1; i < *num; i++)
            memcpy(BASE(i-1),BASE(i),width);
        (*num)--;
        return p;
    }
    return -1;
    
}
int lfv_search(void *key, void *base, size_t *num, size_t width, FCMP fcmp)
{
    int i = 0, j;
    void *v;
    while (fcmp(BASE(i), key) != 0 && i < *num)
        i++;
    if (i >= *num)
        return - 1;
    v = malloc(width);
    //값 가져오기
    memcpy(v, BASE(i), width);
    //
    for (j = i - 1; j >= 0; j--)
        memcpy(BASE(j+1),BASE(j),width);
    memcpy(base,v,width);
    return 0;
}

#define LEN 5
void main(){
    void *p;
    node *t, *head;
    int size = 0, key = 9;
    int data[LEN] = { 3, 1, 9, 7, 5};
    init_list(    ); // using the pointer t
    // Construct your linked list
    // Print out your linked list using for loop and printf()
    // Conduct search with key value
    // Print out the relative position of key value to the starting addr. of LL
}
