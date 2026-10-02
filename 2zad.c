#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};


struct Node* CreateTree(struct Node* r, int data) {
    if (r == NULL) {
        r = (struct Node*)malloc(sizeof(struct Node));
        if (r == NULL) {
            printf("Memory allocation error\n");
            exit(0);
        }
        r->left = NULL;
        r->right = NULL;
        r->data = data;
        return r;
    }

    if (data < r->data) {
        r->left = CreateTree(r->left, data);
    }
    else {
        r->right = CreateTree(r->right, data);
    }

    return r;
}

void print_tree(struct Node* r, int l) {
    if (r == NULL) return;

    print_tree(r->right, l + 1);
    for (int i = 0; i < l; i++) {
        printf("    ");
    }
    printf("%d\n", r->data);
    print_tree(r->left, l + 1);
}

struct Node* FindNode(struct Node* r, int value) {
    if (r == NULL) return NULL;
    if (value == r->data) return r;

    if (value < r->data)
        return FindNode(r->left, value);
    else
        return FindNode(r->right, value);
}

// Function to count occurrences of a specific value
int CountOccurrences(struct Node* r, int value) {
    if (r == NULL) return 0;

    int count = (r->data == value) ? 1 : 0;

    return count + CountOccurrences(r->left, value)
        + CountOccurrences(r->right, value);
}

int main() {
    setlocale(LC_ALL, "");
    int D, start = 1;
    struct Node* root = NULL; 

    printf("-1 - finish building the tree\n");
    while (start) {
        printf("Enter a number: ");
        if (scanf("%d", &D) != 1) break;

        if (D == -1) {
            printf("Tree building finished\n\n");
            start = 0;
        }
        else {
            root = CreateTree(root, D); 
    }

    printf("Tree structure (rotated 90 degrees counter-clockwise):\n");
    print_tree(root, 0);

    printf("\nEnter a value to search for: ");
    scanf("%d", &D);

    struct Node* found = FindNode(root, D);
    if (found != NULL)
        printf("Value %d found in the tree (node address: %p)\n", D, (void*)found);
    else
        printf("Value %d is not present in the tree\n", D);

    // Call the occurrence counter
    int count = CountOccurrences(root, D);
    printf("Value %d occurs in the tree %d time(s)\n", D, count);

    return 0;
}
