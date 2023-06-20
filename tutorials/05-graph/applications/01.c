# include <stdio.h>
# include <stdlib.h>
# include "grafo.h"

enum vcor {
    BRANCO = 0,  // nao visitado
    CINZA,  // visitado mas nao finalizado
    PRETO  // visitado e finalizado
};

struct vertice {
    Aresta *lista;
    VCor cor;
};

struct aresta {
    int v;
    Aresta *prox;
};

struct grafo {
    int n;
    Vertice *v;
};


int main(int argc, char const *argv[])
{
    // cria grafo
    Grafo *g = cria_grafo(5);

    // adiciona arestas
    insere_aresta(g, 0, 1);
    insere_aresta(g, 0, 2);
    insere_aresta(g, 1, 2);
    insere_aresta(g, 2, 3);
    insere_aresta(g, 3, 4);
    insere_aresta(g, 4, 3);
    insere_aresta(g, 4, 1);

    // exibe grafo
    imprime_grafo(g);

    // executa dfs
    grafo_dfs(g, 0);

    // libera memoria
    destroi_grafo(g);

    return 0;
}

// cria grafo com n vertices
Grafo *cria_grafo(int n_vertices)
{
    Grafo *g = (Grafo*) malloc(sizeof(Grafo));
    if (g == NULL) {
        printf("Erro ao alocar memoria para o grafo\n");
        exit(EXIT_FAILURE);
    }
    g->n = n_vertices;
    g->v = (Vertice*) malloc(g->n * sizeof(Vertice));
    
    return g;
}

// insere nova aresta em um determinado vertice
void insere_aresta(Grafo *g, int v1, int v2)
{
    Aresta *a = (Aresta*) malloc(sizeof(Aresta));
    if (a == NULL) {
        printf("Erro ao alocar memoria para a aresta\n");
        exit(EXIT_FAILURE);
    }
    a->v = v2;  // vertice de destino
    a->prox = g->v[v1].lista;  // insere no inicio da lista
    g->v[v1].lista = a;  // atualiza lista de adjacencia
}

// exibe grafo de forma ordenada
void imprime_grafo(Grafo *g)
{
    printf("Grafo:\n");
    for (int i = 0; i < g->n; i++)
    {
        printf("%d: ", i);
        for (Aresta *a = g->v[i].lista; a != NULL; a = a->prox)
        {
            printf("%d ", a->v);
        }
        printf("\n");
    }
}
void destroi_grafo(Grafo *g)
{
    for (int i = 0; i < g->n; i++)
    {
        Aresta *a = g->v[i].lista;
        while (a != NULL)
        {
            Aresta *t = a->prox;
            free(a);
            a = t;
        }
    }
    free(g->v);
    free(g);
}

// inicializa vertice com BRANCO
void inicializa_vertice(Grafo *g, int v)
{
    g->v[v].cor = BRANCO;
}

// inicializa todos os vertices com BRANCO
void inicializa_vertices(Grafo *g)
{
    for (int i = 0; i < g->n; i++)
    {
        inicializa_vertice(g, i);
    }
}

void idfs (Grafo* g, int i)
{
    g->v[i].cor = CINZA;  // visitado
    printf("%d ", i);
    for (Aresta* a = g->v[i].lista; a != NULL; a = a->prox)
    {
        int j = a->v;
        if (g->v[j].cor == BRANCO)
            idfs(g, j);
    }

    g->v[i].cor = PRETO;  // finalizado
}


void grafo_dfs(Grafo *g, int v)
{
    inicializa_vertices(g);
    idfs(g, v);
}