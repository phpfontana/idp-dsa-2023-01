# ifndef __GRAPH_ADJ_LIST_H__
# define __GRAPH_ADJ_LIST_H__

typedef struct graph Graph;
typedef struct vertex Vertex;
typedef struct edge Edge;

typedef enum vcolor VColor;
typedef enum etype EType;

Graph* graph_create(int n);
void graph_destroy(Graph* g);
void graph_add_undirected_edge(Graph* g, int i, int j);
void graph_add_directed_edge(Graph* g, int i, int j);
void graph_show(Graph* g);
void graph_dfs(Graph* g, int v);
static void bfs (Graph *g, int v);
void show_topological_sort(Graph* g);
void show_edge_type(Graph* g);
void show_timestamp(Graph* g);

# endif