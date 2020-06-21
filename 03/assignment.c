#include <stdio.h>
#include <stdlib.h>

#define NUM_STD 10

int main(){
    //make double pointer - 2 by 10 array
    float ** score = (float **) malloc(sizeof(float) * 2);
    for(int i = 0; i < 2; i++){
        score[i] = (float *) malloc(sizeof(float) * NUM_STD);
    }

    //input student score
    //use pointer accumulate <- 사실 그냥 배열로 접근해도 되지만 괜히 포인터 연산좀 써보려고
    for (int i = 0; i < NUM_STD ; i++){
        printf("== input student #%d's term score",i);
        printf("\nmidterm score > ");
        scanf("%f",score[0]+i);
        printf("final score > ");
        scanf("%f",score[1]+i);
    }

    //print avrg score
    printf("\n====avrg score");
    for (int i = 0; i < NUM_STD ; i++){
        printf("\nstudent #%d's avrg score > ",i);
        printf("%f", (score[0][i] + score[1][i])/2);
    }

    //free score
    for(int i = 0; i < 2; i++){
        free(score[i]);
    }
    free(score);
}