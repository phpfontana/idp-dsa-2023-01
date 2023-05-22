# ifndef _SINGLY_H_
# define _SINGLY_H_

typedef struct singly_head List;
typedef struct singly_node Node;

// Operations
List* lst_create (void);
void lst_free (List* l);
void lst_insert (List* l, int v);
void lst_delete (List* l, int v);
int lst_search (List* l, int v);
void lst_display (List* l);

# endif