#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int a[10];
    srand(time(NULL));
    printf("Random numbers:");
    for (int i = 0; i < 10; i++) {
        a[i] = rand() % 100;
        printf("%d ", a[i]);
    }

    return 0;
}
