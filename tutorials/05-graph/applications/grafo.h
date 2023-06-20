# ifndef _GRAFO_H_
# define _GRAFO_H_

typedef struct grafo Grafo;
typedef struct vertice Vertice;
typedef struct aresta Aresta;

typedef enum vcor VCor;

Grafo *cria_grafo(int n_vertices);
void insere_aresta(Grafo *g, int v1, int v2);
void imprime_grafo(Grafo *g);
void destroi_grafo(Grafo *g);
void grafo_dfs(Grafo *g, int v);

# endif