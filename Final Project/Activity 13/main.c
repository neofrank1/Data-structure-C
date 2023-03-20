/*
Filename: Activity 13
Description: Final Project
Programmer: Neo Frank D. Uy
Date: Jan 17, 2021
*/
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

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
struct queue *enqueue(struct queue *, int);
struct queue *dequeue(struct queue *);
struct queue *rejoin(struct queue *);
int peekFront(struct queue *);
int peekRear(struct queue *);
int Count(struct queue *);

struct queue *create_queue(struct queue *q)
{
    q = (struct queue *)malloc(sizeof(struct queue));

	q -> front = NULL;
	q -> rear = NULL;
	return q;
};

struct queue *enqueue(struct queue *q, int value) // Circular enQueue //
{
	struct node *new_queue;

	new_queue = (struct node *)malloc(sizeof(struct node));
	new_queue -> data = value;
	new_queue -> next = NULL;

	if(q -> rear == NULL)
    {
        q -> front = q -> rear = new_queue;
        q -> rear -> next = q -> front;
    }
	else
    {
        q -> rear -> next = new_queue;
    }
	q -> rear = new_queue;

	return q;
};

struct queue *dequeue(struct queue *q) // Circular DeQueue //
{
	struct node *ptr;

	if(q -> front == NULL)
    {
        printf("Queue is empty.");
    }
	else if(q -> front == q -> rear)
	{
		ptr = q -> front;
		q -> front = q -> rear = NULL;
		free(ptr);
	}
	else
	{
		ptr = q -> front;
		q -> front = q -> front -> next;
		free(ptr);
	}

	return q;
}

struct queue *rejoin(struct queue *q) // Rejoin the Message on Queue //
{
	struct node *ptr;

	ptr = q -> front;
	q = dequeue(q);
	q = enqueue(q, ptr -> data);

	return q;
}

int Count(struct queue *q) // Count the Message //
{
	struct node *ptr;
	int count = 0;

    ptr = q -> front;

	while(ptr != NULL)
	{
		count++;
		ptr = ptr -> next;
	}

	return count;
}

int peekFront(struct queue *q)
{
	struct node *ptr;
	ptr = q -> front;
	if (ptr == NULL)
    {
        return 0;
    }
	else
    {
        return ptr -> data;
    }
};

int peekRear(struct queue *q)
{
	struct node *ptr;
	ptr = q -> rear;
	if (ptr == NULL)
    {
        return 0;
    }
	else
    {
        return ptr -> data;
    }
};

int main()
{
    srand(time(NULL));
    q = create_queue(q);

    int hour = 24;
    int second = 60;
    int i;
    int j;
    int k;
    int l;
    int arr;
    int quant;
    int averagePerQue;
    int averagePerMin;
    int averageNum;
    int id;
    int limit;
    int totalMess;
    int totalArr;
    int batches;
    int resend;
    int count;
    int send;
    int reque;
    int store;
    int countMess;
    int arrRate;

    printf("\tMessage Simulator!\t");

    arrRate = 0;
    count = 0;
    countMess = 0;
    store = 0;
    reque = 0;
    send = 0;
    resend = 0;
    totalMess = 0;
    totalArr = 0;
    batches = 0;
    i = 0;

    for (int time=1;time<=24;time++)
    {
    printf("\nTime Remaining: %d Hours",time);

    while(i < hour * second) // Hour //
    {
        while(j<60) // Seconds //
        {
            arr = rand() % 100 + 1; // Arrival of Message //
            if (arr > 30)
            {
             quant = rand() % 3 + 1;  // Quantity of Message //
                if (limit >= 30) // Limit to 30 Message per Sent //
                {
                    break;
                }
                k = 0;
                while(k<quant) // Insert Message in Queue //
                {
                    ++id;
                    k++;
                    q = enqueue(q,200+id);
                }
                totalMess += quant; // Total Messages //
                totalArr += quant; // Total Arrival //
                limit += quant; // Limit of Message // Counter //
            }
            j++;
        }
        ++batches; // Batch of Message Sent //

        limit = 0;
        resend = 0;
        count += Count(q);
        l = 0;
        while(l<40)  // Remove The 40 Messages //
        {
        send = rand() % 200 + 1; // to Know the message need to be send //
        if (send < 100 && q -> front != NULL) // Counter the Sends //
        {
            if(resend <= Count(q)* .25)
            {
                q = rejoin(q);
                ++reque;
                ++resend;
                    if (peekFront(q) - peekRear(q) > 30)
                    {
                        ++store;
                    }
                }
            }
            else if (q -> front != NULL) // Send the Message // Conditional Statement //
            {
                q = dequeue(q);
                ++countMess;
            }
            l++;
        }
        i++;
        j=0;
    }
}

    arrRate = totalArr / batches; // Arrival Rate //
    averagePerMin = countMess / hour * 60; // Average Per Minute //
    averagePerQue = count / hour * 60; // Average Per Queue //
    averageNum = reque / hour * 60; // Average Per Requested //

    // OUTPUT //

    printf("\nThe Message Has Finished Processed");
    printf("\nPRESS ANYTHING TO CONTINUE!");
    getch();
    printf("\n");
    printf("\n");
    printf("\nTotal Message Processed: %d",totalMess);
    printf("\nAverage Arrival Rate: %d",arrRate);
    printf("\nAverage Number of Message Send Per Minute: %d",averagePerMin);
    printf("\nAverage Number of Message in the Queue in a Minute: %d",averagePerQue);
    printf("\nNumber Of Message Send of First Attempt: %d",countMess);
    printf("\nNumber Of Message Send of Second Attempt: %d",reque);
    printf("\nNumber Of Message Send of More Attempt: %d",store);
    printf("\nAverage Number of Times Messages had to be Requested: %d",averageNum);
    printf("\nGoodBye!\n");

    return 0;
}
