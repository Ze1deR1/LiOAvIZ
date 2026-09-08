#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct student {
    char famil[20];
    char name[20];
    char facult[20];
    int Nomzach;
};

int main() {
    struct student stud[3] = {
        {"Ivanov", "Ivan", "Fizmat", 123},
        {"Petrov", "Petr", "Himfak", 456},
        {"Sidorov", "Sidr", "Biofak", 789}
    };

    char search[20] = { 0 };  // инициализируем нулями

    printf("Enter last name to search: ");
    if (scanf_s("%19s", search, (unsigned)sizeof(search)) != 1) {
        printf("Input error!\n");
        return 1;
    }

    int found = 0;
    for (int i = 0; i < 3; i++) {
        if (strcmp(stud[i].famil, search) == 0) {
            printf("Found: %s %s, faculty %s, gradebook %d\n",
                stud[i].famil, stud[i].name, stud[i].facult, stud[i].Nomzach);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Student not found.\n");
    }

    return 0;
}