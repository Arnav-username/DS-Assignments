#include <stdio.h>
#include <stdlib.h>

struct pnode
{
    int coef;
    int exp;
    struct pnode *next;
};

typedef struct pnode pnode;

pnode *getnode(void)
{
    pnode *p = (pnode *)malloc(sizeof(pnode));
    if (p == NULL)
    {
        printf("Memory allocation failed\n");
        exit(1);
    }
    return p;
}

void insert(pnode *head, pnode *newnode)
{
    pnode *p = head->next, *prev = head;
    while (p != head && p->exp > newnode->exp)
    {
        prev = p;
        p = p->next;
    }
    if (p != head && p->exp == newnode->exp)
    {
        p->coef += newnode->coef;
        if (p->coef == 0)
        {
            prev->next = p->next;
            free(p);
        }
        free(newnode);
    }
    else
    {
        newnode->next = p;
        prev->next = newnode;
    }
}

pnode *create(void)
{
    pnode *head = getnode(), *newnode;
    int i, n;
    head->exp = -1;
    head->next = head;
    printf("Enter number of terms: ");
    scanf("%d", &n);
    for (i = 1; i <= n; i++)
    {
        newnode = getnode();
        printf("Enter coefficient and exponent: ");
        scanf("%d%d", &newnode->coef, &newnode->exp);
        newnode->next = NULL;
        insert(head, newnode);
    }
    return head;
}

void display(pnode *head)
{
    pnode *p = head->next;
    if (p == head)
    {
        printf("0\n");
        return;
    }
    while (p != head)
    {
        printf("%dx^%d", p->coef, p->exp);
        p = p->next;
        if (p != head && p->coef > 0) printf(" + ");
        else if (p != head) printf(" ");
    }
    printf("\n");
}

pnode *addPoly(pnode *p1, pnode *p2)
{
    pnode *result = getnode(), *t1 = p1->next, *t2 = p2->next, *curr;
    result->exp = -1;
    result->next = result;
    while (t1 != p1 || t2 != p2)
    {
        curr = getnode();
        if (t1 != p1 && t2 != p2 && t1->exp == t2->exp)
        {
            curr->exp = t1->exp;
            curr->coef = t1->coef + t2->coef;
            t1 = t1->next;
            t2 = t2->next;
        }
        else if (t2 == p2 || (t1 != p1 && t1->exp > t2->exp))
        {
            curr->exp = t1->exp;
            curr->coef = t1->coef;
            t1 = t1->next;
        }
        else
        {
            curr->exp = t2->exp;
            curr->coef = t2->coef;
            t2 = t2->next;
        }
        if (curr->coef == 0)
            free(curr);
        else
        {
            pnode *last = result;
            while (last->next != result) last = last->next;
            curr->next = result;
            last->next = curr;
        }
    }
    return result;
}

void freePoly(pnode *head)
{
    pnode *p = head->next;
    while (p != head)
    {
        pnode *temp = p;
        p = p->next;
        free(temp);
    }
    free(head);
}

int main(void)
{
    pnode *p1, *p2, *sum;
    printf("Create first polynomial\n");
    p1 = create();
    printf("Create second polynomial\n");
    p2 = create();
    printf("First polynomial: ");
    display(p1);
    printf("Second polynomial: ");
    display(p2);
    sum = addPoly(p1, p2);
    printf("Sum: ");
    display(sum);
    freePoly(p1);
    freePoly(p2);
    freePoly(sum);
    return 0;
}