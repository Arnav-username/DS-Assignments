#include <stdio.h>

void displayMatrix(int a[20][20], int r, int c)
{
    int i, j;
    for (i = 0; i < r; i++)
    {
        for (j = 0; j < c; j++)
            printf("%d ", a[i][j]);
        printf("\n");
    }
}

void addMatrix(int Mat1[20][20], int Mat2[20][20], int R1, int R2, int C1, int C2)
{
    int s[20][20], i, j;
    if (R1 == R2 && C1 == C2)
    {
        printf("Addition:\n");
        for (i = 0; i < R1; i++)
            for (j = 0; j < C1; j++)
                s[i][j] = Mat1[i][j] + Mat2[i][j];
        displayMatrix(s, R1, C1);
    }
    else
        printf("Matrices cannot be added\n");
}

void subMatrix(int Mat1[20][20], int Mat2[20][20], int R1, int R2, int C1, int C2)
{
    int m[20][20], i, j;
    if (R1 == R2 && C1 == C2)
    {
        printf("Subtraction:\n");
        for (i = 0; i < R1; i++)
            for (j = 0; j < C1; j++)
                m[i][j] = Mat1[i][j] - Mat2[i][j];
        displayMatrix(m, R1, C1);
    }
    else
        printf("Matrices cannot be subtracted\n");
}

void transpose(int mat[20][20], int r, int c)
{
    int i, j, t[20][20];
    for (i = 0; i < r; i++)
        for (j = 0; j < c; j++)
            t[j][i] = mat[i][j];
    printf("Transpose:\n");
    displayMatrix(t, c, r);
}

void multiMatrix(int Mat1[20][20], int Mat2[20][20], int R1, int R2, int C1, int C2)
{
    int sum, mul[20][20], i, j, k;
    if (C1 == R2)
    {
        printf("Multiplication:\n");
        for (i = 0; i < R1; i++)
            for (j = 0; j < C2; j++)
            {
                sum = 0;
                for (k = 0; k < C1; k++)
                    sum += Mat1[i][k] * Mat2[k][j];
                mul[i][j] = sum;
            }
        displayMatrix(mul, R1, C2);
    }
    else
        printf("Matrices cannot be multiplied\n");
}

int main(void)
{
    int a[20][20], b[20][20], r1, c1, r2, c2, i, j;
    printf("Enter rows and columns of first matrix: ");
    scanf("%d%d", &r1, &c1);
    printf("Enter first matrix:\n");
    for (i = 0; i < r1; i++)
        for (j = 0; j < c1; j++)
            scanf("%d", &a[i][j]);

    printf("Enter rows and columns of second matrix: ");
    scanf("%d%d", &r2, &c2);
    printf("Enter second matrix:\n");
    for (i = 0; i < r2; i++)
        for (j = 0; j < c2; j++)
            scanf("%d", &b[i][j]);

    addMatrix(a, b, r1, r2, c1, c2);
    subMatrix(a, b, r1, r2, c1, c2);
    multiMatrix(a, b, r1, r2, c1, c2);
    printf("First matrix ");
    transpose(a, r1, c1);
    printf("Second matrix ");
    transpose(b, r2, c2);
    return 0;
}