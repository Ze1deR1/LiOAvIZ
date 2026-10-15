#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

#define N 8

int main()
{
    setlocale(LC_ALL, "Russian");

    int A[N][N];
    int i, j;
    int edges = 0;

    srand((unsigned)time(NULL));

    for (i = 0; i < N; i++)
    {
        A[i][i] = 0;
    }

    for (i = 0; i < N; i++)
    {
        for (j = i + 1; j < N; j++)
        {
            A[i][j] = rand() % 2;
            A[j][i] = A[i][j];
        }
    }

    printf("Graph adjacency matrix:\n\n");

    printf("    ");
    for (i = 0; i < N; i++)
    {
        printf("%3d", i + 1);
    }
    printf("\n");

    for (i = 0; i < N; i++)
    {
        printf("%3d ", i + 1);

        for (j = 0; j < N; j++)
        {
            printf("%3d", A[i][j]);
        }

        printf("\n");
    }

    for (i = 0; i < N; i++)
    {
        for (j = i + 1; j < N; j++)
        {
            if (A[i][j] == 1)
            {
                edges++;
            }
        }
    }

    printf("\nGraph size |E| = %d\n", edges);

    printf("\nVertex degrees:\n");

    for (i = 0; i < N; i++)
    {
        int degree = 0;

        for (j = 0; j < N; j++)
        {
            degree += A[i][j];
        }

        printf("deg(v%d) = %d\n", i + 1, degree);
    }

    printf("\nIsolated vertices (degree 0): ");

    int found = 0;

    for (i = 0; i < N; i++)
    {
        int degree = 0;

        for (j = 0; j < N; j++)
        {
            degree += A[i][j];
        }

        if (degree == 0)
        {
            printf("v%d ", i + 1);
            found = 1;
        }
    }

    if (!found)
    {
        printf("none");
    }

    printf("\nLeaf vertices (degree 1): ");

    found = 0;

    for (i = 0; i < N; i++)
    {
        int degree = 0;

        for (j = 0; j < N; j++)
        {
            degree += A[i][j];
        }

        if (degree == 1)
        {
            printf("v%d ", i + 1);
            found = 1;
        }
    }

    if (!found)
    {
        printf("none");
    }

    printf("\nDominant vertices: ");

    found = 0;

    for (i = 0; i < N; i++)
    {
        int degree = 0;

        for (j = 0; j < N; j++)
        {
            degree += A[i][j];
        }

        if (degree == N - 1)
        {
            printf("v%d ", i + 1);
            found = 1;
        }
    }

    if (!found)
    {
        printf("none");
    }

    printf("\n");

    return 0;
}