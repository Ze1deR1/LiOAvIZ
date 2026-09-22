#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//STRUCTUR
struct node
{
    char inf[256];      // payload
    struct node* next;  // pointer to next element
};

struct node* head = NULL, * last = NULL, * f = NULL;
int dlinna = 0;

//PROTOTYPES
void spstore(void);          // push  — add to tail
void review(void);           // print all
void del(char* name);        // delete by content
struct node* find(char* name);
struct node* get_struct(void);
void pop(void);              // pop   — remove from head

//HELPERS
void menu(void)
{
    printf("\n1-add 2-review 3-find 4-delete 5-pop 0-exit\nYour choice: ");
}

void free_all(void)
{
    while (head) { struct node* t = head; head = head->next; free(t); }
}

//CREATE ELEMENT
struct node* get_struct(void)
{
    struct node* p = (struct node*)malloc(sizeof(struct node));
    char s[256];

    if (!p) { printf("Memory allocation error\n"); exit(1); }

    printf("Enter object name: ");
    if (scanf_s("%s", s, (unsigned)sizeof(s)) != 1) { free(p); return NULL; }
    strcpy_s(p->inf, sizeof(p->inf), s);

    p->next = NULL;
    return p;
}

//PUSH
void spstore(void)
{
    struct node* p = get_struct();
    if (!p) return;

    if (!head) { head = last = p; }
    else { last->next = p; last = p; }

    dlinna++;
    printf("Added to queue: %s\n", p->inf);
}

//POP
void pop(void)
{
    if (!head) { printf("Queue is empty\n"); return; }

    struct node* t = head;
    printf("Removed from queue: %s\n", t->inf);

    head = head->next;
    if (!head) last = NULL;
    free(t);
    dlinna--;
}

//REVIEW
void review(void)
{
    if (!head) { printf("Queue is empty\n"); return; }

    printf("\n--- Queue (front -> back) ---\n");
    for (struct node* s = head; s; s = s->next)
        printf("  %s\n", s->inf);
    printf("Size: %d\n", dlinna);
}

//FIND
struct node* find(char* name)
{
    if (!head) { printf("Queue is empty\n"); return NULL; }
    for (struct node* s = head; s; s = s->next)
        if (!strcmp(name, s->inf)) return s;
    printf("Element not found\n");
    return NULL;
}

//DELETE BY CONTENT
void del(char* name)
{
    if (!head) { printf("Queue is empty\n"); return; }

    if (!strcmp(name, head->inf)) {
        struct node* t = head;
        head = head->next;
        if (!head) last = NULL;
        free(t); dlinna--;
        printf("Deleted: %s\n", name);
        return;
    }

    for (struct node* s = head; s->next; s = s->next) {
        if (!strcmp(name, s->next->inf)) {
            struct node* t = s->next;
            s->next = t->next;
            if (t == last) last = s;
            free(t); dlinna--;
            printf("Deleted: %s\n", name);
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
        case 2: review();  break;

        case 3:
            printf("Enter name to find: ");
            if (scanf_s("%s", name, (unsigned)sizeof(name)) != 1) break;
            f = find(name);
            if (f) printf("Found: %s\n", f->inf);
            break;

        case 4:
            printf("Enter name to delete: ");
            if (scanf_s("%s", name, (unsigned)sizeof(name)) != 1) break;
            del(name);
            break;

        case 5: pop(); break;

        case 0: free_all(); return 0;
        default: printf("Invalid menu item\n");
        }
    }
}