# ifndef __BINARY_SEARCH_TREE_H_
# define __BINARY_SEARCH_TREE_H_

// Data Structures
typedef struct _binary_search_tree_node TreeNode;
typedef struct _binary_search_tree Tree;

// Operations
Tree* create_tree(void);
void destroy_tree(Tree* tree);
void insert_node(Tree* tree, int value);
void remove_node(Tree* tree, int value);
TreeNode* search_node(Tree* tree, int value);
void print_tree(Tree* tree);

# endif