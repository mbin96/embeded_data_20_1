#include <stdio.h>
#define ROWS 4 
#define COLS 3

//전역 배열 
int m[ROWS][COLS] = {{1, 3, 5}, {9, 7, 3}, {3, 3, 9}, {2, 8, 6}};

//행의 평균을 리턴하는 함수. 인풋은 배열과 행의 번호
float getRowAvg(int m[][COLS], int r){
    int *start, *end;
    float avg = 0;

    //행의 첫 요소
    start = &m[r][0];
    //행의 끝 요소
    end = &m[r][COLS-1];

    while(start <= end) {
        //요소의 값을 avg에 적산
        avg += *start;
#ifdef DEBUG
        printf("%d\n",*start);
        printf("%f\n",avg);
#endif
        //포인터를 다음 요소로 증가
        start += 1;
    }

    //요소 수로 나누어 평균값 계산
    avg /= COLS;
    return avg ;
}

int main(){
    //getRowAvg 함수 값 출력
    printf("%f\n", getRowAvg(m, 0));
    printf("%f\n", getRowAvg(m, 1));    
    printf("%f\n", getRowAvg(m, 2));    
    printf("%f\n", getRowAvg(m, 3));
}