#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<locale.h>

#define N 8

int main()
{
    setlocale(LC_ALL, "Russian");

    int A[N][N];        // матрица смежности (для генерации рёбер)
    int B[N][N * N];    // матрица инцидентности
    int i, j, e;
    int edges = 0;

    srand((unsigned)time(NULL));

    /* --- генерация матрицы смежности --- */
    for (i = 0; i < N; i++)
        A[i][i] = 0;

    for (i = 0; i < N; i++)
    {
        for (j = i + 1; j < N; j++)
        {
            A[i][j] = rand() % 2;
            A[j][i] = A[i][j];
        }
    }

    /* --- построение матрицы инцидентности --- */
    for (i = 0; i < N; i++)
        for (e = 0; e < N * N; e++)
            B[i][e] = 0;

    e = 0;
    for (i = 0; i < N; i++)
    {
        for (j = i + 1; j < N; j++)
        {
            if (A[i][j] == 1)
            {
                B[i][e] = 1;
                B[j][e] = 1;
                e++;
            }
        }
    }
    edges = e;

    /* --- Задание 1: вывод матрицы инцидентности --- */
    printf("Incidence matrix of graph G:\n\n");

    printf("      ");
    for (e = 0; e < edges; e++)
        printf("%3d", e + 1);
    printf("\n");

    for (i = 0; i < N; i++)
    {
        printf("%3d   ", i + 1);
        for (e = 0; e < edges; e++)
            printf("%3d", B[i][e]);
        printf("\n");
    }

    /* --- Задание 2: размер графа --- */
    printf("\nGraph size |E| = %d\n", edges);

    /* --- Задание 3: степени вершин --- */
    printf("\nVertex degrees:\n");

    for (i = 0; i < N; i++)
    {
        int degree = 0;
        for (e = 0; e < edges; e++)
            degree += B[i][e];
        printf("deg(v%d) = %d\n", i + 1, degree);
    }

    /* --- изолированные вершины --- */
    printf("\nIsolated vertices (degree 0): ");
    int found = 0;
    for (i = 0; i < N; i++)
    {
        int degree = 0;
        for (e = 0; e < edges; e++)
            degree += B[i][e];
        if (degree == 0)
        {
            printf("v%d ", i + 1);
            found = 1;
        }
    }
    if (!found) printf("none");

    /* --- концевые вершины --- */
    printf("\nLeaf vertices (degree 1): ");
    found = 0;
    for (i = 0; i < N; i++)
    {
        int degree = 0;
        for (e = 0; e < edges; e++)
            degree += B[i][e];
        if (degree == 1)
        {
            printf("v%d ", i + 1);
            found = 1;
        }
    }
    if (!found) printf("none");

    /* --- доминирующие вершины --- */
    printf("\nDominant vertices (degree %d): ", N - 1);
    found = 0;
    for (i = 0; i < N; i++)
    {
        int degree = 0;
        for (e = 0; e < edges; e++)
            degree += B[i][e];
        if (degree == N - 1)
        {
            printf("v%d ", i + 1);
            found = 1;
        }
    }
    if (!found) printf("none");

    printf("\n");
    return 0;
}