#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <limits.h>
#include <math.h>

void upheap(int *a, int k)
{
    int v;
    v = a[k];
    a[0] = INT_MAX;
    while (a[k / 2] <= v)//부모노드보다 작으면 끝
    {
        a[k] = a[k / 2];//부모를 자식으로
        k /= 2;
    }
    a[k] = v;
}

void downheap(int *a, int N, int k)
{
    int i, v;
    v = a[k];
    while (k <= N / 2) //자식있는노노드까지
    {
        i = k << 1; //자식노드탐색
        if (i < N && a[i] < a[i + 1])// 노드 벗어나지 않을것, 오른쪽이 더 클것
            i++;//오른쪽 타겟
        if (v >= a[i])//값 비교해서 더 크변 이동 안함
            break;
        a[k] = a[i];//부모(k)가 자식(i)보다 작은경우 값을 이동
        k = i;
    }
    a[k] = v;
}

//heap의 length
void insert(int *a, int *N, int v)
{
    a[++(*N)] = v;//값은 1부터 넣음
    upheap(a, *N);
}

int extract(int *a, int *N)
{
    int v = a[1];
    a[1] = a[(*N)--];
    downheap(a, *N, 1);
    return v;
}

//N 전체 src 크기
// void heap_sort_td(int *src, int* dest, int N)
// {
//     int i;
//     int hn = 0; // # of heap nodes
//     for (i = 1; i <= N; i++)
//         insert(src, &hn, src[i]); 
//     for (i = hn; i >= 1; i--)
//         src[i] = extract(src, &hn); //거꾸로 넣기
// }

int * heap_sort_td(int *a, int N)
{

    int * out = (int *) malloc(sizeof(int) * (N+1));
    memcpy(out+1,a,sizeof(int) * N);
    int i;
    int hn = 0; // # of heap nodes
    for (i = 1; i <= N; i++)
        insert(out, &hn, out[i]);
    for (i = hn; i >= 1; i--)
        out[i] = extract(out, &hn);
    return out;
}

int * heap_sort_bu(int *src, int N)
{
    int k, t;

    int * out = (int *) malloc(sizeof(int) * (N+1));
    memcpy(out+1,src,sizeof(int) * N);
    
    //일단 그대로 넣고 마지막 인ㅌ터널 노드부터 시작
    for (k = N/2;k > 0;k--)
        downheap(out, N, k);
    while (N > 1)
    {     
        t = out[1];
        out[1] = out[N]; 
        out[N] = t;
        downheap(out, --N, 1);
    }
    return out;
}

int * shell_sort(int * a, int N)
{
    int * dest = (int * )malloc(sizeof(int)*N);
    memcpy(dest,a,sizeof(int)*N);
    int i, j, k, h, v;
    for (h = N / 2; h > 0; h = (h)/2)
    {
        for (i = 0; i < h; i++)
        {
            for (j = i + h; j < N; j += h)
            {
                v = dest[j];
                k = j;
                while (k > h - 1 && dest[k - h] > v)
                {
                    dest[k] = dest[k - h];
                    k -= h;
                }
                dest[k] = v;
            }
        }
    }
    return dest;
}




int * getRandom(int n){    
    int *dest = (int * )malloc(n * sizeof(int));
    srand(time(NULL));
    for(int i = 0 ; i < n ; i++){
        dest[i] = rand()%n;
    }
    return dest;
}
int * getSort(int n){    
    int *dest = (int * )malloc(n * sizeof(int));
    srand(time(NULL));
    for(int i = 0 ; i < n ; i++){
        dest[i] = i;
    }
    return dest;
}
int * getInvSort(int n){    
    int *dest = (int * )malloc(n * sizeof(int));
    srand(time(NULL));
    for(int i = 0 ; i < n ; i++){
        dest[i] = n-i;
    }
    return dest;
}


float getRMS(int * orig, int * cmp,int size){
    float sum=0;
    for(int i = 0; i< size; i++){
        sum += sqrt((orig[i]-cmp[i])*(orig[i]-cmp[i]));
    }
        return sum/size;
}

int main(int arg, char *args[]){
    int * arr, size, *out;
    
    // size = 10000;
    size = atoi(args[1]);
    // printf("array size >");
    // scanf("%d",&size);

    arr = getRandom( size);
    
    int * out_td = heap_sort_td(arr, size);
    int * out_bu = heap_sort_bu(arr, size);
    int * out_sh = shell_sort(arr, size);
    printf("rms : %f\n",getRMS(out_sh,out_bu+1,size));

    printf("rms : %f\n",getRMS(out_sh,out_td+1,size));

    
    free(arr);
    arr = getRandom( size);
    



    time_t start,end;
    


    printf("======random======\n");
    start=clock();
    for(int i = 0; i < 100; i++){
        out = heap_sort_td(arr, size);
        free(out);
    }
    end = clock();
    printf("heap sort top-down: %fs\n",(double)(end-start)/CLOCKS_PER_SEC);

    start=clock();
    for(int i = 0; i < 100; i++){
        out = heap_sort_bu(arr, size);
        free(out);
    }
    end = clock();
    printf("heap sort bottom-up: %fs\n",(double)(end-start)/CLOCKS_PER_SEC);

    start=clock();
    for(int i = 0; i < 100; i++){
        out = shell_sort(arr, size);
        free(out);
    }
    end = clock();
    printf("shell sort : %fs\n",(double)(end-start)/CLOCKS_PER_SEC);


    free(arr);
    arr = getSort(size);
    printf("======sorted======\n");
    start=clock();
    for(int i = 0; i < 100; i++){
        out = heap_sort_td(arr, size);
        free(out);
    }
    end = clock();
    printf("heap sort top-down: %fs\n",(double)(end-start)/CLOCKS_PER_SEC);

    start=clock();
    for(int i = 0; i < 100; i++){
        out = heap_sort_bu(arr, size);
        free(out);
    }
    end = clock();
    printf("heap sort bottom-up: %fs\n",(double)(end-start)/CLOCKS_PER_SEC);

    start=clock();
    for(int i = 0; i < 100; i++){
        out = shell_sort(arr, size);
        free(out);
    }
    end = clock();
    printf("shell sort : %fs\n",(double)(end-start)/CLOCKS_PER_SEC);


    free(arr);
    arr = getInvSort(size);

    printf("======invsorted======\n");
    start=clock();
    for(int i = 0; i < 100; i++){
        out = heap_sort_td(arr, size);
        free(out);
    }
    end = clock();
    printf("heap sort top-down: %fs\n",(double)(end-start)/CLOCKS_PER_SEC);

    start=clock();
    for(int i = 0; i < 100; i++){
        out = heap_sort_bu(arr, size);
        free(out);
    }
    end = clock();
    printf("heap sort bottom-up: %fs\n",(double)(end-start)/CLOCKS_PER_SEC);

    start=clock();
    for(int i = 0; i < 100; i++){
        out = shell_sort(arr, size);
        free(out);
    }
    end = clock();
    printf("shell sort : %fs\n",(double)(end-start)/CLOCKS_PER_SEC);

    // for ( int i = 0; i<size; i++ ){
    //     printf("%d ",out[i]);
    // }

    printf("\n");
}