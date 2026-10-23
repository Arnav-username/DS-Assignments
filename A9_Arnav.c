#include <stdio.h>

#define SIZE 100

struct job
{
    int id;
    char title[50];
};

struct job Q[SIZE];
int front = 0, rear = 0;

void addCQ(struct job elem)
{
    if ((rear + 1) % SIZE == front)
        printf("Queue full\n");
    else
    {
        rear = (rear + 1) % SIZE;
        Q[rear] = elem;
        printf("Print job added\n");
    }
}

void delCQ(void)
{
    struct job elem;
    if (front == rear)
        printf("Queue empty\n");
    else
    {
        front = (front + 1) % SIZE;
        elem = Q[front];
        printf("Processed Job ID: %d, Title: %s\n", elem.id, elem.title);
    }
}

void display(void)
{
    int i;
    if (front == rear)
    {
        printf("Queue empty\n");
        return;
    }
    i = (front + 1) % SIZE;
    while (i != (rear + 1) % SIZE)
    {
        printf("Job ID: %d, Title: %s\n", Q[i].id, Q[i].title);
        i = (i + 1) % SIZE;
    }
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
                addCQ(j);
                break;
            case 2: delCQ(); break;
            case 3: display(); break;
        }
    } while (choice != 0);
    return 0;
}