#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* ==================== Shell sort ==================== */

void shell(int* items, int count)
{
    int i, j, gap, k;
    int x, a[5];

    a[0] = 9; a[1] = 5; a[2] = 3; a[3] = 2; a[4] = 1;

    for (k = 0; k < 5; k++) {
        gap = a[k];
        for (i = gap; i < count; ++i) {
            x = items[i];
            for (j = i - gap; (x < items[j]) && (j >= 0); j = j - gap)
                items[j + gap] = items[j];
            items[j + gap] = x;
        }
    }
}

/* ==================== Quick sort ==================== */

void qs(int* items, int left, int right)
{
    int i, j;
    int x, y;

    i = left; j = right;
    x = items[(left + right) / 2];

    do {
        while ((items[i] < x) && (i < right)) i++;
        while ((x < items[j]) && (j > left)) j--;

        if (i <= j) {
            y = items[i];
            items[i] = items[j];
            items[j] = y;
            i++; j--;
        }
    } while (i <= j);

    if (left < j) qs(items, left, j);
    if (i < right) qs(items, i, right);
}

/* ==================== Comparator for qsort ==================== */

int cmp(const void* a, const void* b)
{
    return (*(int*)a - *(int*)b);
}

/* ==================== Timing routine ==================== */

void run_tests(int* src, int n, const char* title)
{
    clock_t s, e;
    int* arr;

    printf("\n%s:\n", title);

    /* --- Shell sort --- */
    arr = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) arr[i] = src[i];
    s = clock();
    shell(arr, n);
    e = clock();
    printf("Shell sort: %f seconds\n", (double)(e - s) / CLOCKS_PER_SEC);
    free(arr);

    /* --- Quick sort --- */
    arr = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) arr[i] = src[i];
    s = clock();
    qs(arr, 0, n - 1);
    e = clock();
    printf("Quick sort: %f seconds\n", (double)(e - s) / CLOCKS_PER_SEC);
    free(arr);

    /* --- qsort --- */
    arr = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) arr[i] = src[i];
    s = clock();
    qsort(arr, n, sizeof(int), cmp);
    e = clock();
    printf("qsort: %f seconds\n", (double)(e - s) / CLOCKS_PER_SEC);
    free(arr);
}

/* ==================== Helper ==================== */

int ask_size(void)
{
    int n;
    printf("Enter array size: ");
    if (scanf("%d", &n) != 1) return -1;
    if (n <= 0) return -1;
    return n;
}

/* ==================== main ==================== */

int main(void)
{
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    srand((unsigned)time(NULL));

    int n;

    /* ---------- 1. Random ---------- */
    n = ask_size();
    if (n <= 0) return 1;
    int* src = (int*)malloc(n * sizeof(int));
    if (!src) return 1;
    for (int i = 0; i < n; i++) src[i] = rand() % 100000 + 1;
    run_tests(src, n, "1. Random array");
    free(src);

    /* ---------- 2. Increasing ---------- */
    n = ask_size();
    if (n <= 0) return 1;
    src = (int*)malloc(n * sizeof(int));
    if (!src) return 1;
    for (int i = 0; i < n; i++) src[i] = i;
    run_tests(src, n, "2. Increasing array");
    free(src);

    /* ---------- 3. Decreasing ---------- */
    n = ask_size();
    if (n <= 0) return 1;
    src = (int*)malloc(n * sizeof(int));
    if (!src) return 1;
    for (int i = 0; i < n; i++) src[i] = n - i;
    run_tests(src, n, "3. Decreasing array");
    free(src);

    /* ---------- 4. Half increasing, half decreasing ---------- */
    n = ask_size();
    if (n <= 0) return 1;
    src = (int*)malloc(n * sizeof(int));
    if (!src) return 1;
    for (int i = 0; i < n / 2; i++)        src[i] = i;
    for (int i = 0; i < n - n / 2; i++)    src[n / 2 + i] = n - i;
    run_tests(src, n, "4. Half increasing, half decreasing");
    free(src);

    printf("\nDone.\n");
    return 0;
}