#include <iostream>
#include <cstdlib>
#include <time.h>

/* Максимальный размер матрицы. Ставим 10000, чтобы хватило на все размеры.
   Три массива 10000 x 10000 x 4 байта = 1.2 ГБ — учтите это. */
const int MAXN = 10000;

/* Массивы глобальные (или static) — иначе стек переполнится.
   Размер известен на этапе компиляции, поэтому VLA не нужен. */
static int a[MAXN][MAXN];
static int b[MAXN][MAXN];
static int c[MAXN][MAXN];

void matrix_multiplication(int n)
{
    clock_t start, end;
    int i = 0, j = 0, r;
    int elem_c;

    srand(time(NULL));
    while (i < n)
    {
        j = 0;
        while (j < n)
        {
            a[i][j] = rand() % 100 + 1;
            j++;
        }
        i++;
    }

    srand(time(NULL));
    i = 0;
    while (i < n)
    {
        j = 0;
        while (j < n)
        {
            b[i][j] = rand() % 100 + 1;
            j++;
        }
        i++;
    }

    start = clock();

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            elem_c = 0;
            for (r = 0; r < n; r++)
            {
                elem_c = elem_c + a[i][r] * b[r][j];
                c[i][j] = elem_c;
            }
        }
    }

    end = clock();

    std::cout << "Size: " << n << " x " << n << std::endl;
    std::cout << "Time: "
        << static_cast<double>(end - start) / CLOCKS_PER_SEC
        << " seconds\n" << std::endl;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int sizes[] = { 100, 200, 400, 1000, 2000, 4000, 10000 };
    int count = sizeof(sizes) / sizeof(sizes[0]);

    for (int k = 0; k < count; k++)
    {
        matrix_multiplication(sizes[k]);
    }

    std::cout << "Done." << std::endl;
    return 0;
}