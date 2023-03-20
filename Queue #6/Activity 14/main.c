/*
Filename: Activity 14
Description: Final Project
Programmer: Neo Frank D. Uy
Date: Jan 17, 2021
*/
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#define FALSE (1==0)
#define TRUE (1==1)

struct node
{
    int data;
    struct node *next;
};

struct queue
{
    struct node *front;
    struct node *rear;
};

struct queue *q;
struct queue *create_queue(struct queue *);
struct queue *enqueue(struct queue *,int);
struct queue *dequeue(struct queue *);
struct queue *display(struct queue *);
int isOperator(char);

int i;
int j = 0;
char expre[20] = "-+*9+28*+4863";
char pre[20];
int total;
int a;
int b;
int c;

struct queue *create_queue(struct queue *q)
{
    q = (struct queue *)malloc(sizeof(struct queue));
    q -> front = NULL;
    q -> rear = NULL;
    return q;
};

int main()
{
    q = create_queue(q);
    i = strlen(expre) - 1;
    while(i>=0)
    {
        pre[j] = expre[i];
        j++;
        i--;
    }
    pre[i] = '\0';

    i = 0;
    while(i<strlen(expre))
    {
        if (pre[i] >= '0' && pre[i] <= '9' )
        {
            c = (int)pre[i] - 48;
            q = enqueue(q,c);
        }
        else if(isOperator(pre[i]) == TRUE)
        {
            if (pre[i] == '+')
            {
                a = q -> rear -> data;
                q = dequeue(q);
                b = q -> rear -> data;
                q = dequeue(q);
                total = a + b;
                q = enqueue(q,total);
            }
            else if (pre[i] == '-')
            {
                a = q -> rear -> data;
                q = dequeue(q);
                b = q -> rear -> data;
                q = dequeue(q);
                total = a - b;
                q = enqueue(q,total);
            }
            else if (pre[i] == '*')
            {
                a = q -> rear -> data;
                q = dequeue(q);
                b = q -> rear -> data;
                q = dequeue(q);
                total = a * b;
                q = enqueue(q,total);
            }
            else if (pre[i] == '/')
            {
                a = q -> rear -> data;
                q = dequeue(q);
                b = q -> rear -> data;
                q = dequeue(q);
                total = a / b;
                q = enqueue(q,total);
            }
        }
        i++;
    }
    printf("\n============================");
    printf("\nTotal:");
    q = display(q);

    return 0;
}

struct queue *enqueue(struct queue *q,int value)
{
    struct node *new_queue;
    new_queue = (struct node *)malloc(sizeof(struct node));
    new_queue -> data = value;

    if (q -> front == NULL)
    {
      q -> front = q -> rear = new_queue;
      q -> rear -> next = q -> front -> next = NULL;;
    }
    else
    {
        q -> rear -> next = new_queue;
        q -> rear = new_queue;
        q -> rear -> next = NULL;
     }
    return q;
};

struct queue *dequeue(struct queue *q)
{
    struct node *ptr,*preptr;

    ptr = q -> front;

    if (q -> front == NULL)
    {
        printf("Empty!");
    }
    else
    {
        if (ptr -> next == NULL)
        {
            q -> front = NULL;
            q -> rear = NULL;
            free(ptr);
        }
        else
        {
            do
            {
                preptr = ptr;
                ptr = ptr -> next;
            }while(ptr -> next != NULL);
            q -> rear = preptr;
            q -> rear -> next = NULL;
            free(ptr);
        }
    }
    return q;
};


struct queue *display(struct queue *q)
{
    struct node *ptr;

    ptr = q -> front;
    if (q -> front == NULL)
    {
        printf("Empty Ang Queue OI!\n");
    }
    else
        {
            do
            {
                printf("%d\t",ptr->data);
                ptr = ptr -> next;
            }while (ptr -> next != NULL);
        }
    return q;
};

int isOperator(char oper)
{
    if (oper == '+' || oper == '-' || oper == '*' || oper == '/')
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}
