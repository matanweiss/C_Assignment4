#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

int main()
{
    char choise = 0;
    pnode head = NULL;
    pnode *arr = NULL;
    while (!('1' <= choise && choise <= '9'))
    {
        switch (choise)
        {
        case 'A':
            build_graph_cmd(&head, &arr);
            break;
        case 'B':
            insert_node_cmd(&head, arr);
            break;
        case 'P':
            printGraph(head);
            break;
        default:
            break;
        }
        scanf(" %c", &choise);
    }
    freeGraph(&head);
    free(arr);
    return 0;
}