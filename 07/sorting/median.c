#include <stdio.h> 
#include <stdlib.h>
void read_file(float *, int, int, char *);
void median_filtering(float *, float *, int, int, int);

void read_file(float *input, int height, int width, char filename[])
{
    int x, y;
    FILE *fp;
    fp = fopen(filename, "r");
    for (y = 0; y < height; y++)
    {
        for (x = 0; x < width; x++)
        {
            fscanf(fp, "%f	", &input[y * width + x]);
            printf("%f ", input[y * width+x]);
        }
        fscanf(fp, "\n");
    }
    fclose(fp);
}

void write_file(float *input, int height, int width, char filename[])
{
    int x, y;
    FILE *fp;
    fp = fopen(filename, "w");
    for (y = 0; y < height; y++)
    {
        for (x = 0; x < width; x++)
        {
            fprintf(fp, "%d	", (int)input[y * width + x]);
           
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
}


void insert_sort(float *a, int N)
{
    int i, j;
    float t;
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

void median_filtering(float * dest, float *src, int height, int width, int size){
    
    int xx, yy, x, y, i, j, count = 0;
    float * filter = (float*) calloc(size*size, sizeof(float));
    int hfSize = size/2;
    for (y = 0; y < height; y++)
    {
        for (x = 0; x < width; x++)
        {
            count = 0;
            for (i = 0; i < size; i++)
            {
                for (j = 0; j < size; j++)
                {
                    yy = y - hfSize + i;
                    xx = x - hfSize + j;
                    if(yy >= 0 && xx >= 0 && yy < height && xx < width){
                        filter[count] = src[(y - hfSize + i) * width + (x - hfSize + j)];
                        count++;
                    }
                }
            }
            insert_sort(filter, count);
            printf("%f",filter[count/2]);
            dest[y * width + x] = filter[count/2];
        }
    }
}

void main()
{
    int height = 44, width = 45; // image width and height

    float * data = (float *) malloc(height * width * sizeof(float));
    float * output = (float *) malloc(height * width * sizeof(float));
    read_file(data,height,width,"noisy_data.txt");
    median_filtering(output, data, height, width, 3);

    write_file(output,height,width,"median_data.txt");
    


}