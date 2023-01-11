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

void build_graph_cmd(pnode *head)
{
    // removing current graph and array
    freeGraph(head);

    // getting number of vertices
    int size = 0;
    scanf("%d", &size);

    // creating vertices
    pnode *arr = createVertices(size);
    *head = arr[0];

    // getting input and creating edges
    int vertex = 0;
    int endVertex = 0;
    int weight = 0;
    char letter = 0;
    for (size_t i = 0; i < size; i++)
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
}

void insert_node_cmd(pnode *head)
{
    int vertex = 0;
    int result = 0;
    int endVertex = 0;
    int weight = 0;
    scanf("%d", &vertex);

    // finding the vertex
    pnode current = *head;
    while (current)
    {
        if (current->node_num == vertex)
        {
            break;
        }
        current = current->next;
    }

    // add vertex if it doesn't exist
    if (!current)
    {
        current = (pnode)malloc(sizeof(node));
        current->node_num = vertex;
        current->edges = NULL;
        current->next = *head;
        *head = current;
    }

    freeEdges(current);

    // getting input and creating edges
    while (1)
    {
        result = scanf("%d", &endVertex);
        if (result == 0)
        {
            break;
        }
        result = scanf("%d", &weight);
        pnode current2 = *head;
        while (current2)
        {
            if (current2->node_num == endVertex)
            {
                addEdge(current, current2, weight);
            }
            current2 = current2->next;
        }
    }
}

void delete_node_cmd(pnode *head)
{

    // getting vertex number
    int vertexNum = 0;
    scanf("%d", &vertexNum);

    // finding vertex
    pnode vertex = *head;
    pnode prev = NULL;
    while (vertex)
    {
        if (vertex->node_num == vertexNum)
        {
            break;
        }
        prev = vertex;
        vertex = vertex->next;
    }

    if (!vertex)
    {
        return;
    }

    // removing edges to vertex
    pnode currentVertex = *head;
    while (currentVertex)
    {
        printf("%d\n", currentVertex->node_num);

        pedge currentEdge = currentVertex->edges;
        pedge prevEdge = NULL;
        while (currentEdge)
        {
            // edge has to be removed
            if (currentEdge->endpoint == vertex)
            {
                // the edge is first, set first edge to its next
                if (!prevEdge)
                {
                    currentVertex->edges = currentEdge->next;
                }

                // the edge is not first, skip the edge
                else
                {
                    prevEdge->next = currentEdge->next;
                }
                free(currentEdge);

                // there is no more than one edge from currentVertex to vertex
                break;
            }
            currentEdge = currentEdge->next;
        }
        currentVertex = currentVertex->next;
    }

    // removing the vertex
    // if the vertex is first
    if (!prev)
    {
        *head = vertex->next;
    }

    // skip the vertex
    else
    {
        prev->next = vertex->next;
    }
    free(vertex);
}

// void delete_node_cmd(pnode *head, pnode *arr)
// {
//     int vertex = 0;
//     scanf("%d", &vertex);
//     if (!arr[vertex])
//     {
//         return;
//     }

//     // removing edges to vertex
//     pnode currentVertex = *head;
//     while (currentVertex)
//     {
//         pedge currentEdge = currentVertex->edges;
//         pedge prev = NULL;
//         if (currentEdge && currentEdge->endpoint == arr[vertex])
//         {
//             currentVertex->edges = currentEdge->next;
//         }
//         while (currentEdge)
//         {
//             if (currentEdge->endpoint == arr[vertex])
//             {
//                 prev->next = prev->next->next;
//             }
//             prev = currentEdge;
//             currentEdge = currentEdge->next;
//         }
//         currentVertex = currentVertex->next;
//     }

//     // removing head
//     if (vertex == 0)
//     {
//         pnode temp = *head;
//         *head = (*head)->next;
//         freeEdges(temp);
//         free(temp);
//         return;
//     }
// }