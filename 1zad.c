#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* root;

struct Node* CreateTree(struct Node* root, struct Node* r, int data)
{
    if (r == NULL)
    {
        r = (struct Node*)malloc(sizeof(struct Node));
        if (r == NULL)
        {
            printf("Memory allocation error");
            exit(0);
        }
        r->left = NULL;
        r->right = NULL;
        r->data = data;
        if (root == NULL) return r;

        if (data > root->data) root->left = r;
        else root->right = r;
        return r;
    }

    if (data > r->data)
        CreateTree(r, r->left, data);
    else
        CreateTree(r, r->right, data);

    return root;
}

void print_tree(struct Node* r, int l)
{
    if (r == NULL) return;

    print_tree(r->right, l + 1);
    for (int i = 0; i < l; i++)
    {
        printf("    ");
    }
    printf("%d\n", r->data);
    print_tree(r->left, l + 1);
}

struct Node* FindNode(struct Node* r, int value)
{
    if (r == NULL)
        return NULL;
    if (value == r->data)
        return r;
    if (value < r->data)
        return FindNode(r->left, value);
    else
        return FindNode(r->right, value);
}

int main()
{
    setlocale(LC_ALL, "");
    int D, start = 1;

    root = NULL;
    printf("-1 - finish building the tree\n");
    while (start)
    {
        printf("Enter a number: ");
        scanf("%d", &D);
        if (D == -1)
        {
            printf("Tree building finished\n\n");
            start = 0;
        }
        else
            root = CreateTree(root, root, D);
    }

    print_tree(root, 0);

    printf("\nEnter a value to search for: ");
    scanf("%d", &D);

    struct Node* found = FindNode(root, D);
    if (found != NULL)
        printf("Value %d found in the tree (node address: %p)\n", D, (void*)found);
    else
        printf("Value %d is not present in the tree\n", D);

    return 0;
}