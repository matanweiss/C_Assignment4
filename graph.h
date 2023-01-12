#ifndef GRAPH_
#define GRAPH_

typedef struct GRAPH_NODE_ *pnode;
;

typedef struct edge_
{
    int weight;
    pnode endpoint;
    struct edge_ *next;
} edge, *pedge;

typedef struct GRAPH_NODE_
{
    int node_num;
    pedge edges;
    struct GRAPH_NODE_ *next;
    int dist;
    int visited;
} node, *pnode;

void build_graph_cmd(pnode *head);
void insert_node_cmd(pnode *head);
void delete_node_cmd(pnode *head);
void deleteGraph_cmd(pnode *head);
void shortsPath_cmd(pnode head);
void TSP_cmd(pnode head);
void freeGraph(pnode *head);
void freeEdges(pnode vertex);
void printGraph(pnode head);
void printEdges(pnode vertex);

#endif