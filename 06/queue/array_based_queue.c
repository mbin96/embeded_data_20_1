#include <stdio.h>

#define MAX 10
int queue[MAX];
int front, rear;

void clear_queue();
void init_queue();
int put(int k);
int get();
void printQueue();

void init_queue()
{
    front = 0;
    rear = 0;
}
void clear_queue()
{
    front = rear;   
}

int put(int k)
{
    if ((rear + 1) % MAX == front)
    {
        printf("Queue overflow !!!\n");
        return -1;
    }
    queue[rear] = k;
    rear = (rear + 1) % MAX;
    return 0;
}
int get()
{
    int j;
    if (front == rear)
    {
        printf("Queue underflow !!!\n");
        return -1;
    }
    j = queue[front];
    front = ++front % MAX;
    return j;
}
void printQueue(){
    printf("===quque print===\n");
    int i = front;
    while(i != rear){
        printf("%d\n",queue[i++]);
        i %= MAX;
    }
    printf("===print end===\n");
}

int main(){
    int k;
    init_queue();
    
    put(3);
    put(6);
    put(9);
    put(1);
    put(6);
    put(3);

    printQueue();

    printf("%d\n",get());

    printQueue();

    put(4);
    put(8);
    put(7);
    put(2);
    put(0);

    // get();
    init_queue();
    printf("%d\n",get());
}



