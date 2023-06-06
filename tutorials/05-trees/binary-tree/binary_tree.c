#include <stdio.h>
#include <stdlib.h>
#include "binary_tree.h"

// Data structures
struct _binary_tree_node
{
    int data;
    TreeNode *left;
    TreeNode *right;
};

struct _binary_tree
{
    TreeNode *root;
};

// Main
int main(int argc, char const *argv[])
{
    // Create a binary tree
    TreeNode *node1 = create_tree_node(1, NULL, NULL);
    TreeNode *node2 = create_tree_node(2, NULL, NULL);
    TreeNode *node3 = create_tree_node(3, NULL, NULL);
    TreeNode *node4 = create_tree_node(4, NULL, NULL);
    TreeNode *node5 = create_tree_node(5, NULL, NULL);
    TreeNode *node6 = create_tree_node(6, NULL, NULL);
    TreeNode *node7 = create_tree_node(7, NULL, NULL);
    TreeNode *node8 = create_tree_node(8, NULL, NULL);

    node1->left = node2;
    node1->right = node3;
    node2->left = node4;
    node4->right = node5;
    node3->left = node6;
    node3->right = node7;
    node7->left = node8;

    Tree *tree = create_tree(node1);

    // Display the tree
    display_dfs_preorder(tree);
    display_dfs_inorder(tree);
    display_dfs_postorder(tree);

    // Search the tree
    TreeNode *node = search_tree(tree, 5);
    if (node != NULL)
        printf("Found: %d\n", node->data);
    else
        printf("Not found.\n");

    // Free the tree
    free_tree(tree);

    return 0;
}

// Operations
Tree *create_tree(TreeNode *root)
{
    Tree *tree = (Tree *)malloc(sizeof(Tree));
    if (tree == NULL)
    {
        printf("Error: memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    tree->root = root;
    return tree;
}

TreeNode *create_tree_node(int data, TreeNode *left, TreeNode *right)
{
    TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
    if (node == NULL)
    {
        printf("Error: memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    node->data = data;
    node->left = left;
    node->right = right;
    return node;
}

void free_tree_node(TreeNode *root)
{
    if (root != NULL)
    {
        free_tree_node(root->left);
        free_tree_node(root->right);
        free(root);
    }
}

void free_tree(Tree *tree)
{
    if (tree != NULL)
    {
        free_tree_node(tree->root);
        free(tree);
    }
}

TreeNode *search(TreeNode *root, int data)
{
    if (root == NULL)
        return NULL;
    else if (root->data == data)
        return root;
    else
    {
        TreeNode *p = search(root->left, data);
        if (p != NULL)
            return p;
        else
            return search(root->right, data);
    }
}

TreeNode *search_tree(Tree *tree, int data)
{
    if (tree == NULL)
        return NULL;
    else
        return search(tree->root, data);
}

void dfs_preorder(TreeNode *root)
{
    if (root != NULL)
    {
        printf("%d ", root->data);
        dfs_preorder(root->left);
        dfs_preorder(root->right);
    }
}

void display_dfs_preorder(Tree *tree)
{
    if (tree != NULL)
    {
        printf("Preorder: ");
        dfs_preorder(tree->root);
        printf("\n");
    }
}

void dfs_inorder(TreeNode *root)
{
    if (root != NULL)
    {
        dfs_inorder(root->left);
        printf("%d ", root->data);
        dfs_inorder(root->right);
    }
}

void display_dfs_inorder(Tree *tree)
{
    if (tree != NULL)
    {
        printf("Inorder: ");
        dfs_inorder(tree->root);
        printf("\n");
    }
}

void dfs_postorder(TreeNode *root)
{
    if (root != NULL)
    {
        dfs_postorder(root->left);
        dfs_postorder(root->right);
        printf("%d ", root->data);
    }
}

void display_dfs_postorder(Tree *tree)
{
    if (tree != NULL)
    {
        printf("Postorder: ");
        dfs_postorder(tree->root);
        printf("\n");
    }
}
