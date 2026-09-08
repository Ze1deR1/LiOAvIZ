#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int n;
    int i;

    printf("Enter array size: ");
    scanf_s("%d", &n);

    int* a = (int*)malloc(n * sizeof(int));

    if (a == NULL)
    {
        printf("Memory allocation error!\n");
        return 1;
    }

    printf("Enter array elements:\n");

    for (i = 0; i < n; i++)
    {
        scanf_s("%d", &a[i]);
    }

    printf("Array:\n");

    for (i = 0; i < n; i++)
    {
        printf("%d ", a[i]);
    }

    free(a);
    return 0;
}