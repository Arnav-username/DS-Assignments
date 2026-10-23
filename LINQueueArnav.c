#include <stdio.h>

#define SIZE 100

struct job
{
    int id;
    char title[50];
};

struct job q[SIZE];
int front = -1, rear = -1;

int isfull(void)
{
    return rear == SIZE - 1;
}

int isempty(void)
{
    return rear == front;
}

void addQ(struct job elem)
{
    if (isfull())
        printf("Queue is full\n");
    else
    {
        if (front == -1) front = 0;
        rear = rear + 1;
        q[rear] = elem;
        printf("Print job added\n");
    }
}

void delQ(void)
{
    struct job elem;
    if (isempty())
        printf("Queue is empty\n");
    else
    {
        elem = q[front];
        front = front + 1;
        printf("Processed Job ID: %d, Title: %s\n", elem.id, elem.title);
        if (front > rear)
            front = rear = -1;
    }
}

void display(void)
{
    int i;
    if (isempty())
    {
        printf("Queue is empty\n");
        return;
    }
    for (i = front; i <= rear; i++)
        printf("Job ID: %d, Title: %s\n", q[i].id, q[i].title);
}

int main(void)
{
    int choice;
    struct job j;
    do
    {
        printf("\n1 Add print job\n2 Process print job\n3 Display pending jobs\n0 Exit\nChoice: ");
        scanf("%d", &choice);
        switch (choice)
        {
            case 1:
                printf("Enter Job ID and document title (one word): ");
                scanf("%d %49s", &j.id, j.title);
                addQ(j);
                break;
            case 2: delQ(); break;
            case 3: display(); break;
        }
    } while (choice != 0);
    return 0;
}