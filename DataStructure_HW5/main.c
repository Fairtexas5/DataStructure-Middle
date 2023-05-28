#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#define MAXLINE 500
typedef struct node
{
    char data[MAXLINE];
    struct node *link;
} NODE;
typedef struct queue
{
    NODE *front;
    NODE *rear;
    int count;
} QUEUE;

QUEUE* CreateQueue(){
    QUEUE* q = (QUEUE*)malloc(sizeof(QUEUE));  
    q->front = NULL;                           
    q->rear = NULL;                            
    q->count = 0;                              
    return q;
}
void Enqueue(QUEUE *q, char* dataIn){
    NODE *newNode = (NODE*)malloc(sizeof(NODE));   
    strcpy(newNode->data, dataIn);                 
    newNode->link = NULL;
    if (q->front == NULL)
        q->front = newNode;                        
    else
        q->rear->link = newNode;
    q->rear = newNode;
    //printf(" New node is %s", dataIn);
    q->count++;                            
}

void Dequeue(QUEUE *q, char *dataOut){
    NODE *temp = q->front;
    strcpy(dataOut, q->front->data);    
    if (q->count == 1)                  
        q->rear = NULL;                 
    q->front = q->front->link;          
    q->count--;                         
    free(temp);
}
int QueueCount(QUEUE *q){
    return q->count;         
}

void Display(QUEUE *q){
    NODE *loc = q->front; // first node
    printf("\n");
    printf("expression: ");
    while (loc != NULL)
    {
        printf("%s ", loc->data);
        loc = loc->link;
    }    
}

void DeleteQueue(QUEUE *q){
    NODE *temp;
    while (q->front != NULL)
    {
        temp = q->front;
        q->front = q->front->link;
        free(temp);
    }
    free(q);
}

int calculate(char a, int b, int c){
     
    if(a=='+')
        return (b+c);
     
    else if(a=='-')
        return (b-c);
    else if(a=='*')
        return (b*c);
    else if(a=='/')
        return (b/c);
    else if (a=='^')
        return (pow(b,c));
    else if (a=='%')
        return (b%c);
    else
        return -1;
}

int calculateExpression(QUEUE *q){

    char data[MAXLINE], dt1[MAXLINE],dt2[MAXLINE],t_opr, t_op1, t_op2, *dptr;
    int i, operand1, operand2, value;

    while ((QueueCount(q)!=1)){
        Dequeue(q, data);
        t_opr=data[0];
        if(ispunct(t_opr)){// if t_opr is punctuation '+' or '_' or '*' or '/'
                dptr=q->front->data;//data pointer is pointing to the 2nd data in the queue
                t_op1=*dptr;
                strcpy(dt1,dptr); // copies the string pointed by dptr to dt1
             
                dptr=q->front->link->data;
                t_op2=*dptr;      //data pointer is poiting to the 3rd data in the queue
                strcpy(dt2,dptr); // copies the string pointed by dptr to dt2
                if(!ispunct(t_op1)&&!ispunct(t_op2)){
                        operand1= atoi (dt1);      
                        operand2= atoi (dt2);       
                        Dequeue(q, dt1);   
                        Dequeue(q, dt2);   
                        value=calculate(t_opr,operand1, operand2);
                        printf (" \n\n Caculation : %d %c %d = %d\n",operand1,t_opr,operand2,value);
                        // itoa (value, data, 10);      
                        sprintf(data,"%d",value);
                        dptr=data;
                        Enqueue(q, dptr);  
                        Display(q);
                    }
                    else{
                        dptr=data;                   
                        Enqueue(q, dptr);   
                        Display(q);
                    }
            }
            else{
                dptr=data;
                Enqueue(q, dptr); 
                Display(q);
            }     
    }
    Dequeue(q, data);
    return atoi(data); 
}

int main(){
    char expr[MAXLINE];
    //Use spaces to differentiate between operators and numbers
    printf("Enter expression: ");
    fgets(expr, MAXLINE, stdin);
    //"- + * 2 3 * 5 4 10" = "16";
    char *token;
    int finalvalue;
    QUEUE *q = CreateQueue();   
    token = expr;
    while ((token = strtok(token, " "))){
        Enqueue(q, token);
        token = NULL;
    }
    finalvalue=calculateExpression(q);
    printf("\n\n value of the expression %d", finalvalue);    
    DeleteQueue(q);  
}
