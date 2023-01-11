#include <stdio.h>
#include <stdlib.h>
// #include <unistd.h>
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

void printGraph(pnode head)
{
    pnode current = head;
    while (current)
    {
        printEdges(current);
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

void freeEdges(pnode vertex)
{
    pedge current = vertex->edges;
    while (current)
    {
        pedge temp = current;
        current = current->next;
        free(temp);
    }
    vertex->edges = NULL;
}

void freeGraph(pnode *head)
{
    pnode current = *head;
    while (current)
    {
        pnode temp = current;
        current = current->next;
        freeEdges(temp);
        free(temp);
    }
}

void build_graph_cmd(pnode *head, pnode **arr, int *size)
{
    // removing current graph and array
    freeGraph(head);
    if (*arr != NULL)
    {
        free(*arr);
    }

    // getting number of vertices
    scanf("%d", size);

    // creating vertices
    *arr = createVertices(*size);
    *head = (*arr)[0];

    // getting input and creating edges
    int vertex = 0;
    int endVertex = 0;
    int weight = 0;
    char letter = 0;
    for (size_t i = 0; i < *size; i++)
    {
        scanf(" %c", &letter);
        scanf("%d", &vertex);
        int result = scanf("%d", &endVertex);
        while (result != 0)
        {
            scanf("%d", &weight);
            addEdge((*arr)[vertex], (*arr)[endVertex], weight);
            result = scanf("%d", &endVertex);
        }
    }
}

void insert_node_cmd(pnode *head, pnode *arr, int size)
{
    int vertex = 0;
    int result = 0;
    int endVertex = 0;
    int weight = 0;
    scanf("%d", &vertex);

    // add vertex if it doesn't exist
    if (!arr[vertex])
    {
        arr[vertex] = (pnode)malloc(sizeof(node));
        arr[vertex]->node_num = vertex - 1;
        arr[vertex]->edges = NULL;
        arr[vertex]->next = NULL;
        if (vertex + 1 < size)
        {
            arr[vertex]->next = arr[vertex + 1];
        }
        if (vertex == 0)
        {
            *head = arr[vertex];
            return;
        }
        arr[vertex - 1]->next = arr[vertex];
    }

    freeEdges(arr[vertex]);

    // getting input and creating edges
    while (1)
    {
        result = scanf("%d", &endVertex);
        if (result == 0)
        {
            break;
        }
        result = scanf("%d", &weight);
        addEdge(arr[vertex], arr[endVertex], weight);
        printf("added edge from %d to %d\n", vertex, endVertex);
    }
}

void delete_node_cmd(pnode *head, pnode *arr)
{
    int vertex = 0;
    scanf("%d", &vertex);
    if (!arr[vertex])
    {
        return;
    }

    // removing edges to vertex
    pnode currentVertex = *head;
    while (currentVertex)
    {
        pedge currentEdge = currentVertex->edges;
        pedge prev = NULL;
        if (currentEdge && currentEdge->endpoint == arr[vertex])
        {
            currentVertex->edges = currentEdge->next;
        }
        while (currentEdge)
        {
            if (currentEdge->endpoint == arr[vertex])
            {
                prev->next = prev->next->next;
            }
            prev = currentEdge;
            currentEdge = currentEdge->next;
        }
        currentVertex = currentVertex->next;
    }

    // removing head
    if (vertex == 0)
    {
        pnode temp = *head;
        *head = (*head)->next;
        freeEdges(temp);
        free(temp);
        return;
    }
}