#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void select_sort(int *a, int N) {
    int min;
    int min_idx;
    int x, y;
    for (y = 0; y < N - 1; y++)
    {
        min_idx = y;
        min = a[y];
        for (x = y + 1; x < N; x++)
        {
            if (min > a[x])
            {
                min = a[x];
                min_idx = x;
            }
        }
        a[min_idx] = a[y];
        a[y] = min;
    }
}

//base -base of array nelem - number of array elements width size of 
void gen_select_sort(void *base, size_t nelem, size_t width, int (*fcmp)(const void *, const void *))
{
    void *min;
    int min_idx;
    int i, j;
    int x, y;
    min = malloc(width);

#ifdef DEBUG
    printf("init  > ",y,min_idx);
    for (int i = 0; i<10; i++ ){
        printf("%d ",*(short *)((char *)base + i*width));
    }
    printf("\n");
    for (int i = 0; i<10; i++ ){
        printf("%d ",*(((short *)base) + i));
    }
    printf("\n");
#endif

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
#ifdef DEBUG
        printf("%d %d > ",y,min_idx);
        for (int i = 0; i<10; i++ ){
            printf("%d ",*(short *)((char *)base + i*width));
        }
        printf("\n");
#endif
    }
    free(min);
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
