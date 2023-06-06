# ifndef _DOUBLY_H_
# define _DOUBLY_H_

typedef struct doubly_head List;
typedef struct doubly_node Node;

// Operations
List* lst_create (void);
void lst_free (List* l);
void lst_insert (List* l, int v);
void insert_last (List* l, int v);
void lst_delete (List* l, int v);
Node* lst_search (List* l, int v);
void lst_display (List* l);

# endif