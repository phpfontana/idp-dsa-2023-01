# include <stdio.h>
# include <stdlib.h>
# include "binary_search_tree.h"

// Data structures
struct _binary_search_tree_node
{
    int data;
    TreeNode *left;
    TreeNode *right;
};

struct _binary_search_tree
{
    TreeNode *root;
};

// Main
int main(int argc, char const *argv[])
{
    // Create a binary search tree
    Tree *tree = create_tree();

    // Insert nodes
    insert_node(tree, 5);
    insert_node(tree, 3);
    insert_node(tree, 7);
    insert_node(tree, 2);
    insert_node(tree, 4);
    insert_node(tree, 6);
    insert_node(tree, 8);

    // Print the tree
    print_tree(tree);

    // Search the tree
    TreeNode *node = search_node(tree, 5);
    if (node != NULL)
        printf("Found: %d\n", node->data);
    else
        printf("Not found.\n");
    
    // Remove nodes
    remove_node(tree, 5);
    remove_node(tree, 3);
    remove_node(tree, 7);

    // Print the tree
    print_tree(tree);

    // Free the tree
    destroy_tree(tree);

    return 0;
}

// Operations
Tree* create_tree(void)
{
    Tree* tree = (Tree*)malloc(sizeof(Tree));
    tree->root = NULL;
    return tree;
}

void destroy(TreeNode* node)
{
    if (node != NULL)
    {
        destroy(node->left);
        destroy(node->right);
        free(node);
    }

    return;
}

void destroy_tree(Tree* tree)
{
    destroy(tree->root);
    free(tree);
    return;
}

TreeNode* insert(TreeNode* root, int value)
{
    if (root == NULL)
    {
        root = (TreeNode*)malloc(sizeof(TreeNode));
        root->data = value;
        root->left = NULL;
        root->right = NULL;
    }
    else if (value < root->data)
        root->left = insert(root->left, value);
    else
        root->right = insert(root->right, value);
    
    return root;
}
void insert_node(Tree* tree, int value)
{
    tree->root = insert(tree->root, value);
    return;
}

TreeNode* remove_aux(TreeNode* root, int value)
{
    if (root == NULL)
        return NULL;
    else if (root->data > value)
        root->left = remove_aux(root->left, value);
    else if (root->data < value)
        root->right = remove_aux(root->right, value);
    else
    {
        if (root->left == NULL && root->right == NULL)
        {
            free(root);
            root = NULL;
        }
        else if (root->left == NULL)
        {
            TreeNode* temp = root;
            root = root->right;
            free(temp);
        }
        else if (root->right == NULL)
        {
            TreeNode* temp = root;
            root = root->left;
            free(temp);
        }
        else
        {
            TreeNode* temp = root->right;
            while (temp->left != NULL)
                temp = temp->left;
            root->data = temp->data;
            root->right = remove_aux(root->right, temp->data);
        }
    }

    return root;
}

void remove_node(Tree* tree, int value)
{
    tree->root = remove_aux(tree->root, value);
    return;

}

TreeNode* search(TreeNode *root, int value)
{
    if (root == NULL)
        return NULL;
    else if (root->data == value)
        return root;
    else if (root->data > value)
        return search(root->left, value);
    else
        return search(root->right, value);
}

TreeNode* search_node(Tree* tree, int value)
{
    return search(tree->root, value);
}

void print(TreeNode* node)
{
    if (node != NULL)
    {
        print(node->left);
        printf("%d ", node->data);
        print(node->right);
    }

    return;
}

void print_tree(Tree* tree)
{
    printf("Tree: ");
    print(tree->root);
    printf("\n");
    return;
}