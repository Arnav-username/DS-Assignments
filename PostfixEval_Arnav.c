#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int stack[100];
int top = -1;

void push(int x)
{
    if (top < 99) stack[++top] = x;
}

int pop(void)
{
    if (top >= 0) return stack[top--];
    return 0;
}

int main(void)
{
    char postfix[100];
    int i, a, b, result;
    printf("Enter postfix expression (single-digit operands): ");
    scanf("%99s", postfix);
    for (i = 0; postfix[i] != '\0'; i++)
    {
        if (isdigit((unsigned char)postfix[i]))
            push(postfix[i] - '0');
        else
        {
            b = pop();
            a = pop();
            switch (postfix[i])
            {
                case '+': result = a + b; break;
                case '-': result = a - b; break;
                case '*': result = a * b; break;
                case '/':
                    if (b == 0) { printf("Division by zero\n"); return 1; }
                    result = a / b;
                    break;
                case '^': result = (int)pow(a, b); break;
                default: printf("Invalid operator\n"); return 1;
            }
            push(result);
        }
    }
    if (top == 0) printf("Result = %d\n", pop());
    else printf("Invalid postfix expression\n");
    return 0;
}