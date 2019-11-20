#include "lem-in.h"

void        printroom(t_room *room)
{
    printf("name = %s\n", room->name);
    printf("x = %zu\n", room->x);
    printf("y = %zu\n", room->y);
    printf("state = %zu\n\n", room->state);
}

void        printpipe(t_pipe *pipe)
{
    printf("a = %s\n", pipe->a);
    printf("b = %s\n", pipe->b);
}

void        printmap(char **map)
{
    int x;

    x = 0;
    while (map[x])
    {
        printf("%s\n", map[x]);
        x++;
    }
}
