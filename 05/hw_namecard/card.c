#define NAME_SIZE 21
#define CORP_SIZE 31
#define TEL_SIZE 16
#define REC_SIZE (NAME_SIZE + CORP_SIZE + TEL_SIZE)

#define FAIL 0
#define SUCCESS 1

typedef struct _stdCard{
    char name[NAME_SIZE];
    char stdNum[NAME_SIZE];
    int midScore;
    int endScore;
    float avagScore;
    struct _stdCard * next;
} stdstdCard;
stdCard * head, * tail;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//function

//init list of stdCard
void initstdCard(){
    head = (stdCard*)calloc(1, sizeof(stdCard));
    tail = (stdCard*)calloc(1, sizeof(stdCard));
    head -> next = tail;
    tail -> next = tail;
}

//add new stdCard to list
void inputstdCard()
{
    //정의
    stdCard *t;
    t = (stdCard *)calloc(1, sizeof(stdCard));

    //data input
    printf("\nInput namestdCard menu: ");
    printf("\nInput name: ");
    gets(t->name);
    printf("\nInput corporation: ");
    gets(t->corp);
    printf("\nInput telephone number: ");
    gets(t->tel);

    //list connect
    t->next = head->next;
    head->next = t;
}
//delete stdCard by name
int deletestdCard(char *name)
{
    stdCard *t, *p;
    p = head;
    t = p->next; //head next
    while (strcmp(name, t->name) != 0 &&t != tail){
        p = p->next; //head next
        t = t->next;
    }
    if (t == tail)
        return FAIL;
    //t뒤에껄 앞에꺼에 연결한뒤 지우기
    p->next = t->next;
    free(t);
    return SUCCESS;
}

stdCard * searchstdCard(char *s)
{
    stdCard *t;
    t = head->next;
    
    while (strcmp(s, t->name) != 0 && t != tail){
        t = t -> next;
    
    }
    if (t == tail)
        return NULL;
    else
        return t;
}

void savestdCard(char *nameOfFile){
    FILE *fp;
    stdCard *t;
    //binary open
    fp = fopen(nameOfFile, "wb");

    t = head->next;
    while (t != tail)
    {
        fwrite(t, REC_SIZE, 1, fp);
        t = t->next;
    }
    
    fclose(fp);
}

void loadstdCard(char *nameOfFile)
{
    FILE *fp;
    stdCard *t, *u;
    fp = fopen(nameOfFile, "rb");
    t = head->next;
    
    //load 하기전에 초기화
    while (t != tail)
    {
        u = t;
        t = t->next;
        free(u);
    }
    head->next = tail;
    
    while (1){
        t = (stdCard *)calloc(1, sizeof(stdCard));
        if (!fread(t, REC_SIZE, 1, fp))//파일 끝까지
        {
            free(t);
            break;
        }
        //head와 다음꺼 사이에 새로 넣기
        t->next = head->next;
        head->next = t;
    }
    fclose(fp);
}

void printHeader(FILE *f)
{
    fprintf(f, "\nName " "Corportation " "Telephone number");
    fprintf(f, "\n-- ------------------- "
        "------------------------------- "
        "---------------------");
}
void printstdCard(stdCard *t, FILE *f)
{
    fprintf(f, "\n % -20s % -30s % -15s", t->name, t->corp, t->tel);
}

int selectMenu()
{
    int j;
    char s[10];
    printf("\nName stdCard Manager");
    printf("\n------------------------");
    printf("\n1.Input name stdCard");
    printf("\n2.Delete name stdCard");
    printf("\n3.Search name stdCard");
    printf("\n4.Load name stdCard");
    printf("\n5.Save name stdCard");
    printf("\n6.Show list");
    printf("\n7.Program end…");
    do
    {
        printf("\n: selection operation->");
        gets(s);
        j = atoi(s);
    } while (j < 0 || j > 7);
    return j;
}


// #include <stdio.h>

void main()
{
    char *fname = "NamestdCard.dat";
    char name[NAME_SIZE];
    int i;
    stdCard *t;
    initstdCard();
    while ((i = selectMenu()) != 7)
    {
        switch (i)
        {
        case 1:
            inputstdCard();
            break;
        case 2:
            printf("\nInput name to delete-> ");
            gets(name);
            if (!deletestdCard(name))
                printf("\nCan’t fine the name…");
            break;
        case 3:
            printf("\nInput name to search-> ");
            gets(name);
            t = searchstdCard(name);
            if (t == NULL)
                break;
            printHeader(stdout);
            printstdCard(t, stdout);
            break;
        case 4:
            loadstdCard(fname);
            break;
        case 5:
            savestdCard(fname);
            break;
        case 6:
            t = head->next;
            printHeader(stdout);
            while (t != tail)
            {
                printstdCard(t, stdout);
                t = t->next;
            }
            break;
        }
        printf("\n\nProgram ends…\n");
    }
}
