#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

int main()
{
    char choise = 0;
    pnode head = NULL;
    // while (choise != '\n')
    while (1)
    {
        switch (choise)
        {
        case 'A':
            build_graph_cmd(&head);
            break;
        case 'Q':
            freeGraph(&head);
            return 0;
        default:
            break;
        }
        scanf(" %c", &choise);
    }
    return 0;
}