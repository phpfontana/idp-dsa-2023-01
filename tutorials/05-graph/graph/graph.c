# include <stdio.h>
# include <stdlib.h>
# include "graph.h"

enum vcolor{
    WHITE = 0,   // not explored
    GRAY,       // being explored
    BLACK      // explored
};

enum atype{
    TREE,
    BACK,
    OTHER  // CROSS or FORWARD
};

struct vertex{
    Edge* list; // other attributes will be here too
    VColor color;
    int it; // initial time
    int ft; // final time
    int prev; // previous vertex
};

struct edge{
    int v; // destination vertex
    Edge* next; // next edge; other attributes
    AType type; // edge type
};

struct graph{
    int n; // number of vertices
    Vertex* v; // vertex vector; other attributes
    unsigned int stamp; // time stamp
};

void init_time(Graph* g){
    g->stamp = 0;
}

int time(Graph* g){
    return g->stamp++;
}

static void init_graph(Graph* g){
    init_time(g);
    for(int i = 0; i < g->n; i++){
        g->v[i].it = -1;
        g->v[i].ft = -1;
        g->v[i].color = WHITE;
        g->v[i].prev = -1;
    }
}

void idfs (Graph* g, int i)
{
    g->v[i].color = GRAY;
    g->v[i].it = time(g);
    for (Edge* a = g->v[i].list; a != NULL; a = a->next)
    {
        int j = a->v;
        if (g->v[j].color == WHITE)
        {
            g->v[j].prev = i;
            a->type = TREE;
            idfs(g, j);
        }
        else if (g->v[j].color == GRAY)
        {
            a->type = BACK;
        }
        else
        {
            a->type = OTHER;
        }
    }
    g->v[i].color = BLACK;
    g->v[i].ft = time(g);
}

void graph_dfs(Graph* g, int v)
{
    idfs(g, v);
}

void show_edge_type(Graph* g)
{   
    printf("Edge types:\n");
    for (int i = 0; i < g->n; i++)
    {
        for (Edge* a = g->v[i].list; a != NULL; a = a->next)
        {
            int j = a->v;
            printf("%d -> %d: type %d\n", i, j, a->type);
        }
    }
}

void show_timestamp (Graph *g)
{
    printf("Timestamps (IT/FT)\n");
    for (int i = 0; i < g->n; i++)
    {
        Vertex v = g->v[i];
        printf("Vertex %d: %d/%d\n", i, v.it, v.ft);
     
    }
}

int main(int argc, char const *argv[])
{
    Graph g;
    g.n = 6; /* 6 vertices */
    g.v = (Vertex*)malloc(6 * sizeof(Vertex));

    // vertex 0
    Edge a03 = {3, NULL};
    Edge a01 = {1, &a03};
    g.v[0].list = &a01;

    // vertex 1
    Edge a14 = {4, NULL};
    Edge a12 = {2, &a14};
    g.v[1].list = &a12;

    // vertex 2
    Edge a25 = {5, NULL};
    Edge a24 = {4, &a25};
    g.v[2].list = &a24;

    // vertex 3
    Edge a31 = {1, NULL};
    g.v[3].list = &a31;

    // vertex 4
    Edge a43 = {3, NULL};
    g.v[4].list = &a43;

    // vertex 5
    Edge a54 = {4, NULL};
    g.v[5].list = &a54;

    init_graph(&g);
    graph_dfs(&g, 0);
    show_edge_type(&g);
    show_timestamp(&g);
    return 0;
}