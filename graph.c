#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

pnode *createVertices(int num)
{
    pnode *arr = (pnode *)malloc(sizeof(pnode) * num);
    if (!arr)
    {
        return NULL;
    }

    arr[num - 1] = (pnode)malloc(sizeof(node));
    arr[num - 1]->next = NULL;
    arr[num - 1]->node_num = num - 1;
    arr[num - 1]->edges = NULL;

    for (int i = num - 2; 0 <= i; i--)
    {
        arr[i] = (pnode)malloc(sizeof(node));
        arr[i]->node_num = i;
        arr[i]->next = arr[i + 1];
        arr[i]->edges = NULL;
    }
    return arr;
}

void printEdges(pnode vertex)
{
    printf("Edges of %d:\n", vertex->node_num);
    pedge current = vertex->edges;
    while (current)
    {
        printf("endVertex: %d, weight: %d\n", current->endpoint->node_num, current->weight);
        current = current->next;
    }
}

void addEdge(pnode vertex, pnode endVertex, int weight)
{
    pedge newEdge = (pedge)malloc(sizeof(edge));
    newEdge->weight = weight;
    newEdge->endpoint = endVertex;
    newEdge->next = vertex->edges;
    vertex->edges = newEdge;
}

void freeNode(pnode vertex)
{
    pedge current = vertex->edges;
    while (current)
    {
        pedge temp = current;
        current = current->next;
        free(temp);
    }
    free(vertex);
}

void freeGraph(pnode *head)
{
    pnode current = *head;
    while (current)
    {
        pnode temp = current;
        current = current->next;
        freeNode(temp);
    }
}

void build_graph_cmd(pnode *head)
{

    // freeGraph(head);

    // getting number of vertices
    int num = 0;
    while (num <= 0)
    {
        scanf("%d", &num);
    }

    // creating vertices
    pnode *arr = createVertices(num);
    *head = arr[0];

    // getting input
    int vertex = 0;
    int endVertex = 0;
    int weight = 0;
    char letter = 0;
    for (size_t i = 0; i < num; i++)
    {
        scanf(" %c", &letter);
        scanf("%d", &vertex);
        int result = scanf("%d", &endVertex);
        while (result != 0)
        {
            scanf("%d", &weight);
            addEdge(arr[vertex], arr[endVertex], weight);
            result = scanf("%d", &endVertex);
        }
    }

    // free allocated memory
    free(arr);
    freeGraph(head);
}