#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    char inf[256];
    int  prior;
    struct node* next;
};

struct node* head = NULL;
struct node* last = NULL;
struct node* f = NULL;
int dlinna = 0;

int input_priority(void) {
    int pr;
    do {
        printf("Enter priority (integer >= 1, 1 is the highest): ");
        if (scanf_s("%d", &pr) != 1) {
            while (getchar() != '\n');
            pr = -1;
            continue;
        }
        if (pr < 1)
            printf("Error: priority must be >= 1. Try again.\n");
    } while (pr < 1);
    return pr;
}

struct node* get_struct(void) {
    struct node* p = (struct node*)malloc(sizeof(struct node));
    if (!p) {
        printf("Memory allocation error\n");
        exit(1);
    }

    printf("Enter name: ");
    scanf_s("%s", p->inf, 256);

    p->prior = input_priority();
    p->next = NULL;
    return p;
}

void insert_node(struct node* p) {
    if (!head) {
        head = last = p;
        return;
    }

    if (p->prior < head->prior) {
        p->next = head;
        head = p;
        return;
    }

    struct node* prev = head;
    struct node* cur = head->next;
    while (cur && cur->prior <= p->prior) {
        prev = cur;
        cur = cur->next;
    }
    prev->next = p;
    p->next = cur;

    if (!cur) last = p;
}

void spstore(void) {
    struct node* p = get_struct();
    insert_node(p);
    dlinna++;
}

void review(void) {
    if (!head) {
        printf("List is empty.\n");
        return;
    }

    printf("\n--- List (from most important to least) ---\n");
    struct node* s = head;
    int i = 1;
    while (s) {
        printf("%d) %-20s priority = %d\n", i++, s->inf, s->prior);
        s = s->next;
    }
    printf("Total elements: %d\n", dlinna);
}

struct node* find(void) {
    char name[256];
    printf("Enter name to search: ");
    scanf_s("%s", name, 256);

    f = NULL;
    struct node* s = head;
    while (s) {
        if (!strcmp(s->inf, name)) {
            f = s;
            break;
        }
        s = s->next;
    }

    if (f)
        printf("Found: %s (priority %d)\n", f->inf, f->prior);
    else
        printf("Not found.\n");

    return f;
}

void del(void) {
    char name[256];
    printf("Enter name to delete: ");
    scanf_s("%s", name, 256);

    if (!head) {
        printf("List is empty.\n");
        return;
    }

    if (!strcmp(name, head->inf)) {
        struct node* t = head;
        head = head->next;
        if (!head) last = NULL;
        free(t);
        dlinna--;
        printf("Deleted.\n");
        return;
    }

    struct node* s = head;
    while (s->next) {
        if (!strcmp(name, s->next->inf)) {
            struct node* t = s->next;
            s->next = t->next;
            if (t == last) last = s;
            free(t);
            dlinna--;
            printf("Deleted.\n");
            return;
        }
        s = s->next;
    }

    printf("Element not found.\n");
}

void change_priority(void) {
    char name[256];
    printf("Enter element name: ");
    scanf_s("%s", name, 256);

    struct node* target = NULL;
    struct node* s = head;
    while (s) {
        if (!strcmp(s->inf, name)) { target = s; break; }
        s = s->next;
    }

    if (!target) {
        printf("Element not found.\n");
        return;
    }

    int new_prior = input_priority();
    if (new_prior == target->prior) {
        printf("Priority unchanged.\n");
        return;
    }

    if (target == head) {
        head = head->next;
        if (!head) last = NULL;
    }
    else {
        struct node* prev = head;
        while (prev->next != target) prev = prev->next;
        prev->next = target->next;
        if (target == last) last = prev;
    }

    target->prior = new_prior;
    target->next = NULL;
    insert_node(target);

    printf("Priority changed.\n");
}

void free_all(void) {
    struct node* t;
    while (head) {
        t = head;
        head = head->next;
        free(t);
    }
    head = last = f = NULL;
    dlinna = 0;
}

void menu(void) {
    printf("\n========== MENU ==========\n");
    printf("1. Add element\n");
    printf("2. Find element\n");
    printf("3. Delete element\n");
    printf("4. Change priority\n");
    printf("5. Show list\n");
    printf("6. Clear list\n");
    printf("0. Exit\n");
    printf("Choice: ");
}

int main(void) {
    int choice;
    int running = 1;

    while (running) {
        menu();
        if (scanf_s("%d", &choice) != 1) {
            while (getchar() != '\n');
            printf("Invalid input.\n");
            continue;
        }

        switch (choice) {
        case 1: spstore();          break;
        case 2: find();             break;
        case 3: del();              break;
        case 4: change_priority();  break;
        case 5: review();           break;
        case 6: free_all();         break;
        case 0: running = 0;        break;
        default: printf("No such option.\n");
        }
    }

    free_all();
    printf("Program finished.\n");
    return 0;
}