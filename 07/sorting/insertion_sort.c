#include <stdlib.h>
#include <stdio.h>

void insert_sort(int *a, int N)
{
    int i, j, t;
    for (i = 1; i < N; i++)
    {
        t = a[i];
        j = i;
        while (j > 0 && a[j - 1] > t)
        {
            a[j] = a[j - 1];
            j--;
        }
        a[j] = t;
    }
}

void indirect_insert_sort(int *a, int *index, int N)
{
    int i, j, t;
    for (i = 0; i < N; i++)
        index[i] = i;
    for (i = 1; i < N; i++)
    {
        t = index[i];
        j = i;
        while (j > 0 &&a[index[j]] > a[t] )
        {
            index[j] = index[j - 1];
            j--;
        }
        index[j] = t;
    }
}


int intcmp(const void *a, const void *b) {
    return (*(int *)a - *(int *)b); 
}
int shortcmp(const void *a, const void *b) {
    return (*(short *)a - *(short *)b); 
}
int floatcmp(const void *a, const void *b) {
    return (*(float *)a - *(float *)b); 
}
void insert_sort(void *base, size_t nelem, size_t width, int (*fcmp)(const void *, const void *))
{
    int i, j;
    void *t;

    for (y = 0; y < nelem - 1; y++)
    {
        min_idx = y;
        memcpy(min, (char *)base + y * width, width); 
        for(x = y+1; x<nelem; x++) {
            if (fcmp(min, (char *)base + x * width) > 0)
            {
                memcpy(min, (char *)base + x * width, width);
                min_idx = x;
            } 
        }
        memcpy((char *)base + min_idx*width, (char *)base + y*width, width); 
        memcpy((char *)base + y*width, min, width);

    }
    free(min);
}

#define SIZE 10
int main(){
    int inum_s[SIZE]  ={3,5,6,2,7,32,5,8,2,6};
    int inum_g[SIZE]  ={3,5,6,2,7,32,5,8,2,6};
    select_sort(inum_s, SIZE);
    gen_select_sort(inum_g, SIZE, sizeof(inum_g[0]), intcmp);
    
    for ( int i = 0; i<SIZE; i++ ){
        printf("%d ",inum_s[i]);
    }
    printf("\n");
    for ( int i = 0; i<SIZE; i++ ){
        printf("%d ",inum_g[i]);
    }
    printf("\n");

    short snum_s[SIZE]  ={3,5,6,2,7,32,5,8,2,6};
    short snum_g[SIZE]  ={3,5,6,2,7,32,5,8,2,6};
    // select_sort(snum_s, SIZE);
    gen_select_sort(snum_g, SIZE, sizeof(snum_g[0]), shortcmp);
    
    for (int i = 0; i<SIZE; i++ ){
        printf("%d ",snum_s[i]);
    }
    printf("\n");
    for (int i = 0; i<SIZE; i++ ){
        printf("%d ",snum_g[i]);
    }
    printf("\n");
    

}

