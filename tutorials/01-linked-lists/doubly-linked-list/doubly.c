# include <stdio.h>
# include <stdlib.h>
# include "doubly.h"

struct doubly_head {
    Node* first;
    Node* last;
};

struct doubly_node {
    int info;
    Node* previous;
    Node* next;
};

int main(int argc, char const *argv[])
{
    List* l = lst_create();
    lst_insert(l, 5);
    lst_insert(l, 4);
    lst_insert(l, 3);
    insert_last(l, 2);
    insert_last(l, 1);

    lst_display(l);

    lst_delete(l, 5);
    lst_delete(l, 1);
    lst_delete(l, 3);

    lst_display(l);
    lst_free(l);

    return 0;
}


List* lst_create (void) {
    List* l = (List*)malloc(sizeof(List));
    if (l == NULL)
        return l;
    l->first = NULL;
    l->last = NULL;
    return l;
}

void lst_free (List* l) {
    Node* aux = l->first;
    while (aux != NULL) {
        Node* t = aux->next;
        free(aux);
        aux = t;
    }
    free(l);
}

void lst_insert (List* l, int v) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (node == NULL)
        return;
    node->info = v;
    node->next = l->first;
    node->previous = NULL;

    if (l->first != NULL)
        l->first->previous = node;
    else
        l->last = node;
    l->first = node;
}

void insert_last (List* l, int v) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (node == NULL)
        return; 
    node->info = v;
    node->previous = l->last; 
    node->next = NULL; 
    if (l->last != NULL)
        l->last->next = node;
    else
        l->first = node;
    l->last = node;
}

void lst_delete (List* l, int v) {
    Node* aux = lst_search(l, v);

    if (aux == NULL)
        return;
    if (aux == l->first)
        l->first = aux->next;
    else
        aux->previous->next = aux->next;
    if (aux == l->last)
        l->last = aux->previous;
    else
        aux->next->previous = aux->previous;
    free(aux);
}

Node* lst_search (List* l, int v) {
    for (Node* aux = l->first; aux != NULL; aux = aux->next)
        if (aux->info == v)
            return aux;
    return NULL;
}

void lst_display (List* l) {
    Node* aux = l->first;

    printf("Doubly Linked List:\n");
    while( aux != NULL) {
        printf("info = %d\n", aux->info);
        aux = aux->next;
    }
}