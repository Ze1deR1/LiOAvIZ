#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node
{
    char inf[256];      // payload
    int  prior;         // priority (higher = more important)
    struct node* next;  // pointer to next element
};

struct node* head = NULL, * last = NULL, * f = NULL;
int dlinna = 0;

char find_el[256];


void spstore(void);
void review(void);
void del(char* name);
struct node* find(char* name);
struct node* get_struct(void);

void menu(void) { printf("\n1-add 2-review 3-find 4-delete 0-exit\nYour choice: "); }
void free_all(void) { while (head) { struct node* t = head; head = head->next; free(t); } }

struct node* get_struct(void)
{
    struct node* p = (struct node*)malloc(sizeof(struct node));
    char s[256];
    int pr;

    if (!p) { printf("Memory allocation error\n"); exit(1); }

    printf("Enter object name: ");
    if (scanf_s("%s", s, (unsigned)sizeof(s)) != 1) { free(p); return NULL; }
    strcpy_s(p->inf, sizeof(p->inf), s);

    printf("Enter priority (integer): ");
    if (scanf_s("%d", &pr) != 1) { free(p); return NULL; }
    p->prior = pr;
    p->next = NULL;
    return p;
}

//PRIORITY
void spstore(void)
{
    struct node* p = get_struct();
    if (!p) return;

    if (!head) { head = last = p; dlinna++; return; }

    if (p->prior > head->prior) { p->next = head; head = p; dlinna++; return; }

    struct node* cur = head;
    struct node* prev = NULL;
    while (cur && cur->prior >= p->prior) { prev = cur; cur = cur->next; }

    prev->next = p;
    p->next = cur;
    if (!cur) last = p;
    dlinna++;
}

//REVIEW
void review(void)
{
    if (!head) { printf("List is empty\n"); return; }
    printf("\n--- Queue (from highest priority to lowest) ---\n");
    for (struct node* s = head; s; s = s->next)
        printf("Name - %-20s Priority - %d\n", s->inf, s->prior);
}

//FIND
struct node* find(char* name)
{
    if (!head) { printf("List is empty\n"); return NULL; }
    for (struct node* s = head; s; s = s->next)
        if (!strcmp(name, s->inf)) return s;
    printf("Element not found\n");
    return NULL;
}

//DELETE
void del(char* name)
{
    if (!head) { printf("List is empty\n"); return; }

    if (!strcmp(name, head->inf)) {
        struct node* t = head;
        head = head->next;
        if (!head) last = NULL;
        free(t); dlinna--;
        return;
    }

    for (struct node* s = head; s->next; s = s->next) {
        if (!strcmp(name, s->next->inf)) {
            struct node* t = s->next;
            s->next = t->next;
            if (t == last) last = s;
            free(t); dlinna--;
            return;
        }
    }
    printf("Element not found\n");
}

//MAIN
int main(void)
{
    int  choice;
    char name[256];

    while (1)
    {
        menu();
        if (scanf_s("%d", &choice) != 1) {
            int c; while ((c = getchar()) != '\n' && c != EOF) {}
            printf("Invalid input\n");
            continue;
        }

        switch (choice)
        {
        case 1: spstore(); break;
        case 2: review(); break;

        case 3:
            printf("Enter name to find: ");
            if (scanf_s("%s", name, (unsigned)sizeof(name)) != 1) break;
            f = find(name);
            if (f) printf("Found: %s (priority %d)\n", f->inf, f->prior);
            break;

        case 4:
            printf("Enter name to delete: ");
            if (scanf_s("%s", name, (unsigned)sizeof(name)) != 1) break;
            del(name);
            break;

        case 0: free_all(); return 0;
        default: printf("Invalid menu item\n");
        }
    }
}