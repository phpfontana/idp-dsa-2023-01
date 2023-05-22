# include <stdio.h>
# include <stdlib.h>
# include "singly.h"

struct singly_head;
struct singly_node;

struct singly_head {
    Node* first;
};

struct singly_node {
    int info;
    Node* next;
};

int main(int argc, char const *argv[])
{
    List* l = lst_create();
    lst_insert (l, 10);
    lst_insert (l, 15);
    lst_insert (l, 20);
    lst_insert (l, 25);
    lst_insert (l, 30);

    lst_display (l);

    lst_delete(l, 30);
    lst_delete(l, 10);
    lst_delete(l, 20);

    lst_display (l);
    lst_free (l);

    return 0;
}


List* lst_create (void)
{
    List* l = (List*)malloc(sizeof(List));
    if (l == NULL)
        return l;
    l->first = NULL;
    return l;
}

void lst_free (List* l)
{
    Node* aux = l->first;
    while (aux != NULL)
    {
        Node* t = aux->next;
        free(aux);
        aux = t;
    }
    free(l);
}

void lst_insert (List* l, int v)
{
    Node* node = (Node*)malloc(sizeof(Node));
    node->info = v;
    node->next = l->first;
    l->first = node;
}

void lst_delete (List* l, int v)
{
    Node* prev = NULL;
    Node* aux = l->first;

    while (aux != NULL && aux->info != v)
    {
        prev = aux;
        aux = aux->next;
    }
    if (aux != NULL) {
        if (prev == NULL)
            l->first = aux->next;
        else 
            prev->next = aux->next;
        free (aux);
    }
}

int lst_search (List* l, int v)
{
    Node* aux = l->first;
    while(aux != NULL)
    {
        aux = aux->next;
        if (aux->info == v)
            return 1;
    }
    return 0;
}

void lst_display (List* l)
{
    Node* aux = l->first;

    printf("Singly Linked List:\n");
    while( aux != NULL)
    {
        printf("info = %d\n", aux->info);
        aux = aux->next;
    }
}