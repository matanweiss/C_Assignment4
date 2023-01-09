#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

int main()
{
    char choise = 0;
    pnode head = NULL;
    // while (choise != '\n')
    while (choise != 'Q')
    {
        switch (choise)
        {
        case 'A':
            build_graph_cmd(&head);
            break;
        case 'Q':
            return 0;
        }
        scanf("%c", &choise);
    }
    return 0;
}