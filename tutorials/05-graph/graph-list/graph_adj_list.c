# include <stdio.h>
# include <stdlib.h>
# include "graph_adj_list.h"

enum vcolor {
    WHITE = 0, // not visited
    GRAY,      // being visited
    BLACK      // visited
};

enum etype {
    TREE,
    BACK,
    OTHER
};

struct vertex {
    Edge* list;          // adjacency list
    enum vcolor color;  // color
    int it;            // initial time
    int ft;           // final time
    int prev;        // previous vertex
};

struct edge {
    int v;             // destination vertex
    Edge* next;       // next edge
    EType type;      // edge type
};

struct graph {
    int n;                // number of vertices
    Vertex* v;           // vertex array
    unsigned int stamp; // time stamp
};

int main()
{
    // Initialize graph
    Graph* g = graph_create(6);

    // Add edges
    graph_add_undirected_edge(g, 0, 1);
    graph_add_undirected_edge(g, 0, 2);
    graph_add_undirected_edge(g, 1, 3);
    graph_add_undirected_edge(g, 2, 3);
    graph_add_undirected_edge(g, 2, 4);
    graph_add_undirected_edge(g, 3, 5);
    graph_add_undirected_edge(g, 4, 5);

    // Show graph
    graph_show(g);

    // Run DFS
    graph_dfs(g, 0);

    // Show edge types
    show_edge_type(g);

    // Show timestamps
    show_timestamp(g);

    // Run BFS
    bfs(g, 0);

    // Show edge types
    show_edge_type(g);

    // Show timestamps
    show_timestamp(g);

    // Show topological sort
    show_topological_sort(g);

    // Destroy graph
    graph_destroy(g);

    return 0;
}

static void init_time(Graph* g)
{
    g->stamp = 0;
}

static int time(Graph* g)
{
    return g->stamp++;
}

static void init(Graph* g)
{
    init_time(g);
    for (int i = 0; i < g->n; i++)
    {
        g->v[i].color = WHITE;
        g->v[i].it = -1;
        g->v[i].ft = -1;
        g->v[i].prev = -1;
    }
}

static void idfs(Graph* g, int i)
{
    g->v[i].color = GRAY;
    g->v[i].it = time(g);
    for (Edge* e = g->v[i].list; e != NULL; e = e->next)
    {
        int j = e->v;
        if (g->v[j].color == WHITE)
        {
            g->v[j].prev = i;
            e->type = TREE;
            idfs(g, j);
        }
        else if (g->v[j].color == GRAY)
        {
            e->type = BACK;
        }
        else
        {
            e->type = OTHER;
        }
    }
    g->v[i].color = BLACK;
    g->v[i].ft = time(g);
}

void graph_dfs(Graph* g, int v)
{
    idfs(g, v);
}

// topological sort
void show_topological_sort(Graph* g)
{
    idfs(g, 0);

    int *order = malloc(g->n * sizeof(int));
    for (int i = 0; i < g->n; i++)
    {
        order[i] = i;
    }

    for (int i = 0; i < g->n; i++)
    {
        for (int j = i + 1; j < g->n; j++)
        {
            if (g->v[order[i]].ft < g->v[order[j]].ft)
            {
                int tmp = order[i];
                order[i] = order[j];
                order[j] = tmp;
            }
        }
    }

    printf("Topological sort:\n");
    for (int i = 0; i < g->n; i++)
    {
        printf("%d ", order[i]);
    }

    printf("\n");
    free(order);


}

void show_edge_type(Graph* g)
{
    printf("Edge types:\n");
    for (int i = 0; i < g->n; i++)
    {
        printf("%d: ", i);
        for (Edge* e = g->v[i].list; e != NULL; e = e->next)
        {
            int j = e->v;
            printf("%d -> %d: type %d\n", i, j, e->type);
        }
        printf("\n");
    }
}

void show_timestamp(Graph* g)
{
    printf("Timestamps: (IT/FT)\n");
    for (int i = 0; i < g->n; i++)
    {
        Vertex* v = &g->v[i];
        printf("Vertex %d: %d/%d\n", i, v->it, v->ft);      
    }
    printf("\n");
}

Graph* graph_create(int n)
{
    Graph* g = (Graph*) malloc(sizeof(Graph));
    g->n = n;
    g->v = (Vertex*) malloc(n * sizeof(Vertex));
    for (int i = 0; i < n; i++)
    {
        g->v[i].list = NULL;
    }
    return g;
}

void graph_destroy(Graph* g)
{
    for (int i = 0; i < g->n; i++)
    {
        Edge* e = g->v[i].list;
        while (e != NULL)
        {
            Edge* next = e->next;
            free(e);
            e = next;
        }
    }
    free(g->v);
    free(g);
}

void graph_add_edge(Graph* g, int i, int j)
{
    Edge* e = (Edge*) malloc(sizeof(Edge));
    e->v = j;
    e->type = OTHER;
    e->next = g->v[i].list;
    g->v[i].list = e;
}

void graph_add_undirected_edge(Graph* g, int i, int j)
{
    graph_add_edge(g, i, j);
    graph_add_edge(g, j, i);
}

void graph_add_directed_edge(Graph* g, int i, int j)
{
    graph_add_edge(g, i, j);
}

void graph_show(Graph* g)
{
    printf("Graph:\n");
    for (int i = 0; i < g->n; i++)
    {
        printf("%d: ", i);
        for (Edge* e = g->v[i].list; e != NULL; e = e->next)
        {
            int j = e->v;
            printf("%d ", j);
        }
        printf("\n");
    }
    printf("\n");
}

static void bfs (Graph *g, int v)
{
    // init Queue
    int *queue = (int *) malloc (g->n * sizeof(int));
    int start = 0;
    int end = 0;

    // first element in queue
    g->v[v].color = GRAY;
    g->v[v].it = time(g);
    g->v[v].prev = -1;
    queue[end++] = v;

    // while queue is not empty
    while (start != end)
    {
        // get first element
        int i = queue[start++];

        // for each edge
        for (Edge *e = g->v[i].list; e != NULL; e = e->next)
        {
            int j = e->v;
            if (g->v[j].color == WHITE)
            {
                g->v[j].color = GRAY;
                g->v[j].it = time(g);
                g->v[j].prev = i;
                queue[end++] = j;
            }
            else 
            {
                if (g->v[j].color == GRAY)
                {
                    e->type = BACK;
                }
                else 
                {
                    e->type = OTHER;
                }
            }  
        }
        g->v[i].color = BLACK;
        g->v[i].ft = time(g);      
    }
}