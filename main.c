#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

int main()
{
    char choise = 0;
    pnode head = NULL;
    while (!feof(stdin))
    {
        switch (choise)
        {
        case 'A':
            build_graph_cmd(&head);
            break;
        case 'B':
            insert_node_cmd(&head);
            break;
        case 'D':
            delete_node_cmd(&head);
            break;
        case 'S':
            shortsPath_cmd(head);
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
    return 0;
}