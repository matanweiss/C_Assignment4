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
    printf("\n");
    pnode current = head;
    while (current)
    {
        printEdges(current);
        current = current->next;
    }
    printf("\n");
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

    // do nothing
    if (size == 0)
    {
        return;
    }

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
    free(arr);
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
            prevEdge = currentEdge;
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

pnode findMinNotVisited(pnode head)
{
    int min = __INT_MAX__;
    pnode result = NULL;
    while (head)
    {
        if (!head->visited && head->dist < min)
        {
            min = head->dist;
            result = head;
        }
        head = head->next;
    }
    return result;
}

int shortsPath_cmd(pnode head, int sourceNum, int destNum)
{
    pnode source = NULL;
    pnode dest = NULL;
    pnode current = head;

    // finding both vertices and resetting values
    while (current)
    {
        current->dist = __INT_MAX__;
        current->visited = 0;
        if (current->node_num == sourceNum)
        {
            source = current;
            source->dist = 0;
        }
        else if (current->node_num == destNum)
        {
            dest = current;
        }
        current = current->next;
    }

    // running dijkstra's algorithm
    current = findMinNotVisited(head);
    while (current)
    {
        current->visited = 1;
        pedge currentEdge = current->edges;
        while (currentEdge)
        {
            if (!currentEdge->endpoint->visited && current->dist + currentEdge->weight < currentEdge->endpoint->dist)
            {
                currentEdge->endpoint->dist = current->dist + currentEdge->weight;
            }
            currentEdge = currentEdge->next;
        }
        current = findMinNotVisited(head);
    }
    if (dest->dist == __INT_MAX__)
    {
        dest->dist = -1;
    }
    return dest->dist;
}

void swap(int *nums, int num1, int num2)
{
    int temp = nums[num1];
    nums[num1] = nums[num2];
    nums[num2] = temp;
}

void printArray(int *arr, int k)
{
    printf("[%d", *arr);
    for (size_t i = 1; i < k; i++)
    {
        printf(", %d", *(arr + i));
    }
    printf("]\n");
}

void check(pnode head, int *arr, int k, int curr, int *result)
{
    // if there are only two vertices
    if (k == 2)
    {
        int dist = shortsPath_cmd(head, arr[0], arr[1]);
        if (dist != -1 && (curr + dist) < *result)
        {
            *result = (curr + dist);
        }
        return;
    }

    // check other paths recursively
    for (int i = 1; i < k; i++)
    {
        swap(arr, 1, i);
        int dist = shortsPath_cmd(head, arr[0], arr[1]);
        if (dist == -1)
        {
            return;
        }
        check(head, arr + 1, k - 1, curr + dist, result);
        swap(arr, i, 1);
    }
}

void TSP_cmd(pnode head)
{
    // getting input and inserting number to an array
    int k;
    scanf("%d", &k);
    int *nums = (int *)(malloc(sizeof(int) * k));
    int result = __INT_MAX__;
    for (int i = 0; i < k; i++)
    {
        scanf("%d", &nums[i]);
    }

    // checking every possible vertex to start from
    for (int i = 0; i < k; i++)
    {
        swap(nums, 0, i);
        check(head, nums, k, 0, &result);
        swap(nums, i, 0);
    }

    if (result == __INT_MAX__)
    {
        result = -1;
    }
    free(nums);
    printf("TSP shortest path: %d\n", result);
}
