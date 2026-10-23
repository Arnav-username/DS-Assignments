#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX 200

char opStack[MAX];
int top;

void pushChar(char x) { if (top < MAX - 1) opStack[++top] = x; }
char popChar(void) { if (top >= 0) return opStack[top--]; return '\0'; }
char peekChar(void) { if (top >= 0) return opStack[top]; return '\0'; }

int icp(char ch)
{
    if (ch == '+' || ch == '-') return 1;
    if (ch == '*' || ch == '/') return 2;
    if (ch == '^') return 4;
    if (ch == '(') return 5;
    return 0;
}

int isp(char ch)
{
    if (ch == '+' || ch == '-') return 1;
    if (ch == '*' || ch == '/') return 2;
    if (ch == '^') return 3;
    return 0;
}

int operand(char c) { return isalnum((unsigned char)c); }

void infixToPostfix(char in[], char out[])
{
    int i, k = 0;
    top = -1;
    for (i = 0; in[i] != '\0'; i++)
    {
        char c = in[i];
        if (c == ' ') continue;
        if (operand(c)) out[k++] = c;
        else if (c == '(') pushChar(c);
        else if (c == ')')
        {
            while (top >= 0 && peekChar() != '(') out[k++] = popChar();
            if (top >= 0) popChar();
        }
        else
        {
            while (top >= 0 && peekChar() != '(' && isp(peekChar()) >= icp(c))
                out[k++] = popChar();
            pushChar(c);
        }
    }
    while (top >= 0) out[k++] = popChar();
    out[k] = '\0';
}

void reverseString(char s[])
{
    int i, j;
    char t;
    for (i = 0, j = (int)strlen(s) - 1; i < j; i++, j--)
    {
        t = s[i]; s[i] = s[j]; s[j] = t;
    }
}

void infixToPrefix(char in[], char out[])
{
    char rev[MAX], post[MAX];
    int i;
    strcpy(rev, in);
    reverseString(rev);
    for (i = 0; rev[i] != '\0'; i++)
    {
        if (rev[i] == '(') rev[i] = ')';
        else if (rev[i] == ')') rev[i] = '(';
    }
    infixToPostfix(rev, post);
    strcpy(out, post);
    reverseString(out);
}

void postfixToInfix(char in[], char out[])
{
    char st[MAX][MAX], a[MAX], b[MAX];
    int t = -1, i;
    for (i = 0; in[i] != '\0'; i++)
    {
        char c = in[i];
        if (c == ' ') continue;
        if (operand(c))
        {
            st[++t][0] = c;
            st[t][1] = '\0';
        }
        else
        {
            if (t < 1) { strcpy(out, "Invalid expression"); return; }
            strcpy(b, st[t--]);
            strcpy(a, st[t--]);
            snprintf(st[++t], MAX, "(%s%c%s)", a, c, b);
        }
    }
    if (t == 0) strcpy(out, st[t]);
    else strcpy(out, "Invalid expression");
}

void postfixToPrefix(char in[], char out[])
{
    char st[MAX][MAX], a[MAX], b[MAX];
    int t = -1, i;
    for (i = 0; in[i] != '\0'; i++)
    {
        char c = in[i];
        if (c == ' ') continue;
        if (operand(c))
        {
            st[++t][0] = c;
            st[t][1] = '\0';
        }
        else
        {
            if (t < 1) { strcpy(out, "Invalid expression"); return; }
            strcpy(b, st[t--]);
            strcpy(a, st[t--]);
            snprintf(st[++t], MAX, "%c%s%s", c, a, b);
        }
    }
    if (t == 0) strcpy(out, st[t]);
    else strcpy(out, "Invalid expression");
}

void prefixToInfix(char in[], char out[])
{
    char st[MAX][MAX], a[MAX], b[MAX];
    int t = -1, i;
    for (i = (int)strlen(in) - 1; i >= 0; i--)
    {
        char c = in[i];
        if (c == ' ') continue;
        if (operand(c))
        {
            st[++t][0] = c;
            st[t][1] = '\0';
        }
        else
        {
            if (t < 1) { strcpy(out, "Invalid expression"); return; }
            strcpy(a, st[t--]);
            strcpy(b, st[t--]);
            snprintf(st[++t], MAX, "(%s%c%s)", a, c, b);
        }
    }
    if (t == 0) strcpy(out, st[t]);
    else strcpy(out, "Invalid expression");
}

void prefixToPostfix(char in[], char out[])
{
    char st[MAX][MAX], a[MAX], b[MAX];
    int t = -1, i;
    for (i = (int)strlen(in) - 1; i >= 0; i--)
    {
        char c = in[i];
        if (c == ' ') continue;
        if (operand(c))
        {
            st[++t][0] = c;
            st[t][1] = '\0';
        }
        else
        {
            if (t < 1) { strcpy(out, "Invalid expression"); return; }
            strcpy(a, st[t--]);
            strcpy(b, st[t--]);
            snprintf(st[++t], MAX, "%s%s%c", a, b, c);
        }
    }
    if (t == 0) strcpy(out, st[t]);
    else strcpy(out, "Invalid expression");
}

int main(void)
{
    int choice;
    char exp[MAX], result[MAX];
    do
    {
        printf("\n1 Infix to Postfix\n2 Infix to Prefix\n3 Postfix to Infix\n4 Postfix to Prefix\n5 Prefix to Infix\n6 Prefix to Postfix\n0 Exit\nChoice: ");
        scanf("%d", &choice);
        if (choice == 0) break;
        printf("Enter expression (single-character operands, no spaces needed): ");
        scanf("%199s", exp);
        switch (choice)
        {
            case 1: infixToPostfix(exp, result); break;
            case 2: infixToPrefix(exp, result); break;
            case 3: postfixToInfix(exp, result); break;
            case 4: postfixToPrefix(exp, result); break;
            case 5: prefixToInfix(exp, result); break;
            case 6: prefixToPostfix(exp, result); break;
            default: strcpy(result, "Invalid choice");
        }
        printf("Result: %s\n", result);
    } while (choice != 0);
    return 0;
}