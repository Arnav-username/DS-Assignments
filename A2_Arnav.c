#include <stdio.h>

#define MAX 400

void compact(int a[20][20], int m, int n, int b[MAX][3])
{
    int i, j, k = 1;
    b[0][0] = m;
    b[0][1] = n;
    for (i = 0; i < m; i++)
        for (j = 0; j < n; j++)
            if (a[i][j] != 0)
            {
                b[k][0] = i;
                b[k][1] = j;
                b[k][2] = a[i][j];
                k++;
            }
    b[0][2] = k - 1;
}

void displaySparse(int b[MAX][3])
{
    int i;
    for (i = 0; i <= b[0][2]; i++)
        printf("%d\t%d\t%d\n", b[i][0], b[i][1], b[i][2]);
}

void transpose(int a[MAX][3], int b[MAX][3])
{
    int m = a[0][0], n = a[0][1], t = a[0][2];
    int q = 1, col, p;
    b[0][0] = n;
    b[0][1] = m;
    b[0][2] = t;
    if (t <= 0)
        return;
    for (col = 0; col < n; col++)
        for (p = 1; p <= t; p++)
            if (a[p][1] == col)
            {
                b[q][0] = a[p][1];
                b[q][1] = a[p][0];
                b[q][2] = a[p][2];
                q++;
            }
}

void fastTranspose(int a[MAX][3], int b[MAX][3])
{
    int s[20] = {0}, tpos[20], m = a[0][0], n = a[0][1], terms = a[0][2];
    int i, j;
    b[0][0] = n;
    b[0][1] = m;
    b[0][2] = terms;
    if (terms <= 0)
        return;
    for (i = 1; i <= terms; i++)
        s[a[i][1]]++;
    tpos[0] = 1;
    for (i = 1; i < n; i++)
        tpos[i] = tpos[i - 1] + s[i - 1];
    for (i = 1; i <= terms; i++)
    {
        j = a[i][1];
        b[tpos[j]][0] = a[i][1];
        b[tpos[j]][1] = a[i][0];
        b[tpos[j]][2] = a[i][2];
        tpos[j]++;
    }
}

int main(void)
{
    int a[20][20], sparse[MAX][3], tr[MAX][3], ftr[MAX][3];
    int m, n, i, j;
    printf("Enter rows and columns: ");
    scanf("%d%d", &m, &n);
    printf("Enter matrix:\n");
    for (i = 0; i < m; i++)
        for (j = 0; j < n; j++)
            scanf("%d", &a[i][j]);

    compact(a, m, n, sparse);
    printf("Sparse representation (row column value):\n");
    displaySparse(sparse);
    transpose(sparse, tr);
    printf("Simple transpose:\n");
    displaySparse(tr);
    fastTranspose(sparse, ftr);
    printf("Fast transpose:\n");
    displaySparse(ftr);
    return 0;
}