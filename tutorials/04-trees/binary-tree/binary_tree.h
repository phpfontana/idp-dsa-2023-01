# ifndef _BINARY_TREE_H_
# define _BINARY_TREE_H_

typedef struct _binary_tree_node TreeNode;

typedef struct _binary_tree Tree;

// Operations
Tree *create_tree(TreeNode *root);
TreeNode *create_tree_node(int data, TreeNode *left, TreeNode *right);
TreeNode *search_tree(Tree *tree, int data);
void free_tree(Tree *tree);
void display_dfs_preorder(Tree *tree);
void display_dfs_inorder(Tree *tree);
void display_dfs_postorder(Tree *tree);

# endif