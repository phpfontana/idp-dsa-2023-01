# include <stdio.h>
# include <stdlib.h>

enum vcolor {
    WHITE = 0, // not visited
    GRAY,      // being visited (children being visited)
    BLACK      // visited
};

struct vertex {
    enum vcolor color;
    // Other vertex properties
};

struct graph {
    int n;               // number of vertices
    int **adj;          // adjacency matrix
    struct vertex *v;  // vertex array
};

static void idfs(struct graph *g, int i)
{
    printf("%d ", i);
    g->v[i].color = GRAY;
    for (int j = 0; j < g->n; j++)
    {
        if (!g->adj[i][j])
            continue; // No edge

        if (g->v[j].color == WHITE)
            idfs(g, j);
    }

    g->v[i].color = BLACK;
}

/* exported dfs function */
void graph_dfs(struct graph *g, int v)
{
    idfs(g, v);
}

static void ibfs(struct graph *g, int i)
{
    // initialize queue
    int *queue = malloc(g->n * sizeof(int));
    int ini = 0, end = 0;

    // insert first element in queue
    queue[end++] = i;

    while (ini != end)
    {
        int u = queue[ini++];
        printf("%d ", u);
        g->v[u].color = GRAY;
        for (int j = 0; j < g->n; j++)
        {
            if (!g->adj[u][j])
                continue; // No edge

            if (g->v[j].color == WHITE)
            {
                queue[end++] = j;
                g->v[j].color = GRAY;
            }
        }
        g->v[u].color = BLACK;
    }
}

/* exported bfs function */
void graph_bfs(struct graph *g, int v)
{
    ibfs(g, v);
}

// create graph 
struct graph *graph_create(int n)
{
    struct graph *g = malloc(sizeof(struct graph));
    g->n = n;
    g->adj = malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
        g->adj[i] = calloc(n, sizeof(int));
    g->v = calloc(n, sizeof(struct vertex));
    return g;
}

// add edge
void graph_add_edge(struct graph *g, int u, int v)
{
    g->adj[u][v] = 1;
}

// free graph
void graph_free(struct graph *g)
{
    for (int i = 0; i < g->n; i++)
        free(g->adj[i]);
    free(g->adj);
    free(g->v);
    free(g);
}

// init graph
void graph_init(struct graph *g)
{
    for (int i = 0; i < g->n; i++)
        g->v[i].color = WHITE;
}

// topological sort
void graph_topological_sort(struct graph *g)
{
    graph_init(g);
    for (int i = 0; i < g->n; i++)
        if (g->v[i].color == WHITE)
            graph_dfs(g, i);
}



int main(int argc, char const *argv[])
{
    struct graph *g = graph_create(6);
    graph_add_edge(g, 0, 1);
    graph_add_edge(g, 0, 3);
    graph_add_edge(g, 1, 2);
    graph_add_edge(g, 1, 4);
    graph_add_edge(g, 2, 4);
    graph_add_edge(g, 2, 5);
    graph_add_edge(g, 3, 1);
    graph_add_edge(g, 4, 3);
    graph_add_edge(g, 5, 4);

    graph_init(g);
    graph_dfs(g, 0);
    printf("\n");

    graph_init(g);
    graph_bfs(g, 0);
    printf("\n");

    graph_topological_sort(g);  // same as dfs

    graph_free(g);
    return 0;
}