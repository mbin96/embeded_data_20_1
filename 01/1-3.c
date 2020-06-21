#include <stdio.h>


int pointer1(){
    int j = 9;
    int *p = &j;

    int i = 9;
    int *q = NULL;
    q = &j;
}

int pointer2(){
    int j = 9;
    float f = 9.3;
    int *pj = NULL;

    // int *pf = NULL;
    float *pf = NULL;
    pj = &j;
    pf = &f;
    printf("%d\n", *pj);
    printf("%f\n", *pf);
}
int pointer3(){
    int j = 9;
    int *p = NULL;

    p = &j;

    printf("j = %d\n", j); // 원래 값
    printf("p = %d\n", p); // 주소
    printf("*p = %d\n", *p); //디레퍼렌싱

}
int pointer4(){
    int x = 9, y = 39;
    
    int *p;
    p = &x;
    printf("*p = %d\n", *p);
    
    p = &y;
    printf("*p = %d\n", *p);
    
}

int pointer5(){
    int j = 9;
    int *p;

    p = &j;
    printf("j = %d\n", j);
    
    //포인터로 역참조해서 값 바뀜
    *p = 39;
    printf("j = %d\n", j);
    
}

void pointer_op1(){
    char *pc;
    int *pi;
    float *pf;
    pc = (char *)1000;
    pi = (int *)1000;
    pf = (float *)1000;
    printf("%d, %d, %d\n", pc+2, pi+2, pf+2 );
    //>>1002, 1008, 1008
    //Check pc+2, pi+2, pf+2 !
}

void pointer_op2()
{
    int j = 9; int *p = &j;
    printf("j = %d,  p = %d\n", j, p); 
    (*p)++; 
    printf("j = %d,  p = %d\n", j, p);
    printf("j = %d,  p = %d\n", j, p); 
    printf("%d",*p++);
    printf("j = %d,  p = %d\n", j, p);

}

void pointer_op3_1(){
    int a = 9;
    int b = 39;
    int *pt;
    pt = &a;
    b = *pt;
    printf("b value = %d\n", b);

}
void pointer_op3_2()
{
    // int a = 9; -- rev.1 실행시 세그멘테이션 에러
    int a[2] = {9,0}; //rev.1 대체
    int *pt1, *pt2;
    // pt1 = &a; -- rev.2 gcc에서 컴파일 워닝, 실행시 값이 의도와 다름, 스택 스매싱 발생
    // pt2 = &a+1; -- rev.2 gcc에서 컴파일 워닝, 실행시 값이 의도와 다름, 스택 스매싱 발생
    pt1 = &a[0];    //rev.2 대체
    pt2 = &a[0]+1;  //rev.2 대체
    *pt2 = 39;
    printf("%d\n", *(pt1+1));
    printf("%d\n", *(pt1)+1);
}
void pointer_cast()
{
    char buffer[8];
    int *pi;

    pi = (int *)buffer;
    *pi = 12;       //buffer[0:3]
    *(pi+1) = 34;   //buffer[4:7]
    printf("%d\n%d\n",*pi, *(pi+1));

    printf("%d\n%d\n",pi, (pi+1));
}


int main(){
    printf("\n-------ex1------- \n");
    pointer1();
    
    printf("\n-------ex2------- \n");
    pointer2();
    
    printf("\n-------ex3------- \n");
    pointer3();
    printf("\n-------ex4------- \n");
    pointer4();
    printf("\n-------ex5------- \n");
    pointer5();
    printf("\n-------ex6------- \n");
    pointer_op1();
    printf("\n-------ex7------- \n");
    pointer_op2();
    printf("\n-------ex8------- \n");
    pointer_op3_2();
    printf("\n-------ex9------- \n");
    pointer_cast();
}

