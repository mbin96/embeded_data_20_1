#include <stdio.h>

int pointer1(){
    int a = 9;
    int b = 39;
    int *pt;

    pt = &a;
    b = *pt;

    printf("a value : %d\n",a);
    printf("b value(역참조값) : %d\n",b);
}

int pointer2(){
    int a = 9;
    int *b = &a;
    int *pt;

    pt = b;

    printf("result(역참조값) : %d\n",*pt);
}

void array_dum(){
    int score[5];
    score[0] = 95;
    score[1] = 95;
    score[2] = 95;
    score[3] = 95;
    score[4] = 95;
}
void array_clav(){
    int i;
    int score[5];
    for(i = 0; i < 5; i++){
        score[i] = 95;
    }
}
#define SIZE 5
void array_cp(){
    int a[SIZE] = {1,2,3,4,5};
    int * b;

    //포인터를 이용해 주소만
    b = a; //pt만 복사
    
    printf("b : ");
    for(int i = 0; i < SIZE; i++){
        printf("%d", b[i]);
    }
    printf("\n");


    //물리값을 복사 0부터 시작
    int c[SIZE] = {0,};
    for (int i = 0; i<SIZE; i++){
        c[i] = a[i]; //값 복사
    }
    
    printf("c : ");
    for(int i = 0; i < SIZE; i++){
        printf("%d", c[i]);
    }
    printf("\n");
    
    
}

void array_size(){
    int score[] = {97, 88, 83, 79, 65, 58, 92, 89, 77, 81, 60};
    int size;
    size = sizeof(score) / sizeof(score[0]);
    printf("size of array = %d\n", size);
}

int main(){
    printf("\n-------ex1------- \n");
    pointer1();
    printf("\n-------ex2------- \n");
    pointer2();
    printf("\n-------ex3------- \n");
    
    array_cp();
    printf("\n-------ex4------- \n");
    array_size();
    // array_dum();
    printf("\n-------ex5------- \n");
    
    // array_clav();

}



#include "stdafx.h" 
#include <Windows.h> #include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
#define Fs 16000 #define Bits 16 #define REC_DUR 3
void CALLBACKwaveInProc(HWAVEIN hwi, UINT uMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2) { if (uMsg == WIM_DATA) printf("데이타가 다 채워졌읍니다.\n"); }
void CALLBACKwaveOutProc(HWAVEIN hwi, UINT uMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2) { if (uMsg == WIM_DATA) printf("데이타가 다 채워졌읍니다.\n"); }
int main() {
    WAVEFORMATEX     my_wave_format; HWAVEIN     h_input; HWAVEOUT    h_output; WAVEHDR     w_header; short int* Buf = new short int[Fs * REC_DUR];
    my_wave_format.wFormatTag = WAVE_FORMAT_PCM; my_wave_format.nChannels = 1; my_wave_format.nSamplesPerSec = Fs; my_wave_format.wBitsPerSample = Bits; my_wave_format.nBlockAlign = my_wave_format.nChannels * my_wave_format.wBitsPerSample / 8; my_wave_format.nAvgBytesPerSec = my_wave_format.nSamplesPerSec * my_wave_format.nBlockAlign; my_wave_format.cbSize = 0;
    waveInOpen(&h_input, WAVE_MAPPER, &my_wave_format, (DWORD_PTR)waveInProc, 0L, CALLBACK_FUNCTION); waveOutOpen(&h_output, WAVE_MAPPER, &my_wave_format, (DWORD_PTR)waveOutProc, 0L, CALLBACK_FUNCTION);
    w_header.lpData = (LPSTR)Buf; w_header.dwBufferLength = Fs * REC_DUR * sizeof(short); w_header.dwFlags = w_header.dwLoops = 0L;
    waveInPrepareHeader(h_input, &w_header, sizeof(WAVEHDR)); memset(Buf, 0, Fs * REC_DUR * sizeof(short)); waveInAddBuffer(h_input, &w_header, sizeof(WAVEHDR)); printf("아무키나 누르면 녹음이 시작됩니다.\n"); getchar();
    waveInStart(h_input); Sleep(4000);
    waveOutPrepareHeader(h_output, &w_header, sizeof(WAVEHDR)); waveOutWrite(h_output, &w_header, sizeof(WAVEHDR)); Sleep(4000);
    waveInReset(h_input); waveInUnprepareHeader(h_input, &w_header, sizeof(WAVEHDR)); waveInClose(h_input);
    waveOutReset(h_output); waveOutClose(h_output);
    return 0;
}