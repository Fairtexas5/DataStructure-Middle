#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct node{
    char data[16];
    struct node *link;
} NODE;

typedef struct queue{
    NODE *front;
    NODE *back;
    int count;
} QUEUE;

QUEUE* CreateQueue(){
    QUEUE* q = (QUEUE*)malloc(sizeof(QUEUE));
    q->front = NULL;
    q->back = NULL;
    q->count = 0;
    return q;
}
/* back --->////// <---front ; gorsel olarak ifade edersek */
/*  enqueue --> ////// <--dequeue ; gorsel olarak ifade edersek */
//first in, first out

void Enqueue(QUEUE *q, char* veriGiris){
    NODE *newDugum = (NODE*)malloc(sizeof(NODE));
    strcpy(newDugum->data, veriGiris);
    newDugum->link = NULL;
    if (q->front == NULL)
        q->front = newDugum;
    else
        q->back->link = newDugum;
    q->back = newDugum;
    q->count++;
}

void Dequeue(QUEUE *q, char *veriCikis){
    NODE *temp = q->front;
    strcpy(veriCikis, q->front->data); //strcpy kendisinin string olan ikinci degiskenini kopyalar
    if (q->count == 1)
        q->back = NULL;
    q->front = q->front->link;
    q->count--;
    free(temp);
}

int QueueCount(QUEUE *q){
    return q->count;
}

void Display(QUEUE *q){
    NODE *pLoc = q->front; // ilk kuyruk
    printf("\n");
    printf("Hesaplanacak olan ifade: ");
    while (pLoc != NULL){
        printf("%s ", pLoc->data);
        pLoc = pLoc->link;}
}

void DestroyQueue(QUEUE *q){
    NODE *temp;
    while (q->front != NULL)
    {
        temp = q->front;
        q->front = q->front->link;
        free(temp);
    }
    free(q);
}

int Hesapislemi(char a, int b, int c){
    if(a=='-')
        return (b-c);
    else if(a=='+')
        return (b+c);
    else if(a=='*')
        return (b*c);
    else if(a=='/')
        return (b/c);
    else
        return -1;
}

void stringKopya(char veri1[],char* veriptr){
    int i=0;
    while(*veriptr!='\0'){
        veri1[i]=*veriptr;
        veriptr++;
        i++;}
    veri1[i]='\0';
}

int HesaplananDeger(QUEUE *q)
{
    char data[16], veri1[16],veri2[16],temp_opr, temp_op1, temp_op2, *veriptr;
  int i, operand1, operand2, value;
    while ((QueueCount(q)!=1))
    {
        Dequeue(q, data);
        temp_opr=data[0];
        if(ispunct(temp_opr))// eger, temp_opr noktalama isareti '+' veya '_' veya '*' veya '/' ise
        {
            veriptr=q->front->data;//verinin pointeri 2. datayi gosterirken
            temp_op1=*veriptr;
            stringKopya(veri1,veriptr); // veriptr tarafindan gosterilen dizeyi veri1'e kopyalar

            veriptr=q->front->link->data;
            temp_op2=*veriptr;      //verinin pointeri 3. datayi gosterirken
            stringKopya(veri2,veriptr); // veriptr tarafindan gosterilen dizeyi veri2'ye kopyalar
            if(!ispunct(temp_op1)&&!ispunct(temp_op2))
            {
                operand1= atoi (veri1);
                operand2= atoi (veri2);
                Dequeue(q, veri1);
                Dequeue(q, veri2);
                value=Hesapislemi(temp_opr,operand1, operand2);
                printf (" \n\n Islemden sonra %d %c %d = %d\n\n",operand1,temp_opr,operand2,value);

                sprintf(data,"%d",value);
                veriptr=data;
                Enqueue(q, veriptr);
                Display(q);
            }
            else
            {
                veriptr=data;
                Enqueue(q, veriptr);
                Display(q);
            }
        }
        else
        {
            veriptr=data;
            Enqueue(q, veriptr);
            Display(q);
        }
    }
    Dequeue(q, data);
    return atoi(data);
}

int main()
{
    char expr[200] = "- + * 9 + 2 8 * + 4 8 6 3";
    char *token;
    int Sonuc;
    QUEUE *q = CreateQueue();
    token = expr;
    while ((token = strtok (token, " ")))
    {
        Enqueue(q, token);
        token = NULL;
    }
    Sonuc=HesaplananDeger(q);
    printf("\n\n Hesaplanan Deger %d \n\n", Sonuc);
    DestroyQueue(q);

    return 0;
}
