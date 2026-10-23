#include <stdio.h>
#include <stdlib.h>

struct node
{
    int regNo;
    char name[50];
    struct node *next;
};

typedef struct node node;
node *head;

void create(void)
{
    node *temp = head, *curr;
    char choice;
    do
    {
        curr = (node *)malloc(sizeof(node));
        if (curr == NULL) return;
        printf("Enter registration number and name (one word): ");
        scanf("%d %49s", &curr->regNo, curr->name);
        curr->next = NULL;
        temp->next = curr;
        temp = curr;
        printf("Add another student? (y/n): ");
        scanf(" %c", &choice);
    } while (choice == 'y' || choice == 'Y');
}

void display(void)
{
    node *curr = head->next;
    if (curr == NULL)
    {
        printf("List is empty\n");
        return;
    }
    while (curr != NULL)
    {
        printf("RegNo: %d, Name: %s\n", curr->regNo, curr->name);
        curr = curr->next;
    }
}

int len(void)
{
    int i = 0;
    node *curr = head->next;
    while (curr != NULL)
    {
        i++;
        curr = curr->next;
    }
    return i;
}

void insertByPos(void)
{
    node *curr = head, *nnode;
    int pos, i = 1, k = len();
    nnode = (node *)malloc(sizeof(node));
    if (nnode == NULL) return;
    printf("Enter registration number and name (one word): ");
    scanf("%d %49s", &nnode->regNo, nnode->name);
    printf("Enter position: ");
    scanf("%d", &pos);
    if (pos < 1 || pos > k + 1)
    {
        printf("Data can't be inserted\n");
        free(nnode);
        return;
    }
    while (curr != NULL && i < pos)
    {
        i++;
        curr = curr->next;
    }
    nnode->next = curr->next;
    curr->next = nnode;
}

void deleteByPos(void)
{
    node *prev = head, *curr, *temp;
    int pos, ctr = 1, k = len();
    printf("Enter position to delete: ");
    scanf("%d", &pos);
    if (pos < 1 || pos > k)
    {
        printf("Data can't be deleted\n");
        return;
    }
    curr = head->next;
    while (ctr < pos && curr != NULL)
    {
        ctr++;
        prev = curr;
        curr = curr->next;
    }
    temp = curr;
    prev->next = curr->next;
    curr->next = NULL;
    free(temp);
}

void reverse(void)
{
    node *prev = NULL, *curr = head->next, *future;
    while (curr != NULL)
    {
        future = curr->next;
        curr->next = prev;
        prev = curr;
        curr = future;
    }
    head->next = prev;
}

void sort(void)
{
    int i, j, l = len();
    node *prev, *curr, *temp;
    for (i = 1; i < l; i++)
    {
        prev = head;
        curr = head->next;
        for (j = 0; j < l - i; j++)
        {
            temp = curr->next;
            if (curr->regNo > temp->regNo)
            {
                prev->next = temp;
                curr->next = temp->next;
                temp->next = curr;
                prev = temp;
            }
            else
            {
                prev = curr;
                curr = curr->next;
            }
        }
    }
}

int main(void)
{
    int choice;
    head = (node *)malloc(sizeof(node));
    if (head == NULL) return 1;
    head->next = NULL;
    do
    {
        printf("\n1 Create list\n2 Insert by position\n3 Delete by position\n4 Display\n5 Count participants\n6 Sort by registration number\n7 Reverse list\n0 Exit\nChoice: ");
        scanf("%d", &choice);
        switch (choice)
        {
            case 1: create(); break;
            case 2: insertByPos(); break;
            case 3: deleteByPos(); break;
            case 4: display(); break;
            case 5: printf("Total participants: %d\n", len()); break;
            case 6: sort(); break;
            case 7: reverse(); break;
        }
    } while (choice != 0);
    while (head != NULL)
    {
        node *temp = head;
        head = head->next;
        free(temp);
    }
    return 0;
}