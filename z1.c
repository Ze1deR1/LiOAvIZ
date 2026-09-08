#include <stdio.h>

int main() {
    int a[10] = {3, 7, 1, 9, 4, 6, 8, 2, 5, 0};
    int max = a[0], min = a[0];

    for (int i = 1; i < 10; i++) {
        if (a[i] > max) max = a[i];
        if (a[i] < min) min = a[i];
    }

    printf("Разница: %d\n", max - min);
    return 0;
}