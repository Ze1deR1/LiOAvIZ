#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<locale.h>

#define MAX_N 20   // максимальный размер графа

int main()
{
    setlocale(LC_ALL, "Russian");

    int A[MAX_N][MAX_N];        // матрица смежности
    int B[MAX_N][MAX_N * MAX_N];// матрица инцидентности
    int N;                      // размер графа (выбирает пользователь)
    int i, j, e;
    int edges = 0;
    int oriented;               // 1 — ориентированный, 0 — неориентированный
    int percent;                // вероятность появления ребра в процентах

    srand((unsigned)time(NULL));

    /*Выбор размера графа*/
    printf("Enter graph size N (2..%d): ", MAX_N);
    scanf("%d", &N);

    if (N < 2 || N > MAX_N)
    {
        printf("Invalid size. Using N = 8.\n");
        N = 8;
    }

    /*Выбор типа графа*/
    printf("Graph type (1 - oriented, 0 - non-oriented): ");
    scanf("%d", &oriented);

    /*Выбор вероятности появления ребра*/
    printf("Enter edge probability in percent (0..100): ");
    scanf("%d", &percent);

    if (percent < 0) percent = 0;
    if (percent > 100) percent = 100;

    /*Генерация матрицы смежности*/
    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++)
            A[i][j] = 0;

    for (i = 0; i < N; i++)
    {
        if (oriented)
        {
            // Ориентированный
            for (j = 0; j < N; j++)
            {
                if (i != j && (rand() % 100) < percent)
                    A[i][j] = 1;
            }
        }
        else
        {
            // Неориентированный
            for (j = i + 1; j < N; j++)
            {
                if ((rand() % 100) < percent)
                {
                    A[i][j] = 1;
                    A[j][i] = 1;
                }
            }
        }
    }

    /*Построение матрицы инцидентности*/
    for (i = 0; i < N; i++)
        for (e = 0; e < N * N; e++)
            B[i][e] = 0;

    e = 0;

    if (oriented)
    {
        // Для ориентированного
        for (i = 0; i < N; i++)
        {
            for (j = 0; j < N; j++)
            {
                if (A[i][j] == 1)
                {
                    B[i][e] = 1;    // начало
                    B[j][e] = -1;   // конец 
                    e++;
                }
            }
        }
    }
    else
    {
        // Для неориентированного
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
    }

    edges = e;

    /*Задание 1: вывод матрицы инцидентности*/
    printf("\nIncidence matrix of graph G:\n\n");

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

    /*Задание 2: размер графа*/
    printf("\nGraph size |E| = %d\n", edges);

    /*Задание 3: степени вершин*/
    printf("\nVertex degrees:\n");

    for (i = 0; i < N; i++)
    {
        int degree = 0;

        if (oriented)
        {
            // Для ориентированного
            int outDeg = 0, inDeg = 0;
            for (e = 0; e < edges; e++)
            {
                if (B[i][e] == 1)  outDeg++;
                if (B[i][e] == -1) inDeg++;
            }
            printf("v%d: out = %d, in = %d, total = %d\n",
                i + 1, outDeg, inDeg, outDeg + inDeg);
            degree = outDeg + inDeg;
        }
        else {
            for (e = 0; e < edges; e++)
                degree += B[i][e];
            printf("deg(v%d) = %d\n", i + 1, degree);
        }
    }

    /*Изолированные вершины*/
    printf("\nIsolated vertices: ");
    int found = 0;
    for (i = 0; i < N; i++)
    {
        int degree = 0;
        for (e = 0; e < edges; e++)
        {
            if (B[i][e] == 1 || B[i][e] == -1)
                degree++;
        }
        if (degree == 0)
        {
            printf("v%d ", i + 1);
            found = 1;
        }
    }
    if (!found) printf("none");

    /*Концевые вершины*/
    printf("\nLeaf vertices: ");
    found = 0;
    for (i = 0; i < N; i++)
    {
        int degree = 0;
        for (e = 0; e < edges; e++)
        {
            if (B[i][e] == 1 || B[i][e] == -1)
                degree++;
        }
        if (degree == 1)
        {
            printf("v%d ", i + 1);
            found = 1;
        }
    }
    if (!found) printf("none");

    /*Доминирующие вершины*/
    printf("\nDominant vertices: ");
    found = 0;
    for (i = 0; i < N; i++)
    {
        int degree = 0;
        for (e = 0; e < edges; e++)
        {
            if (B[i][e] == 1 || B[i][e] == -1)
                degree++;
        }
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