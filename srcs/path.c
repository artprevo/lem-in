#include "lem-in.h"

// static t_path   init_path(t_env *env, t_room *room, t_pipe *pipe)
// {
//     // t_room  *tmp;
//     int     path;
//
//     // tmp = env->room;
//     // while (pipe->prev)
//     //     pipe = pipe->prev;
//     path = 0;
//     while (pipe)
//     {
//         if (pipe->a == room->name)
//         {
//             pipe->used = TRUE;
//             room->used = TRUE;
//             path = 1;
//         }
//     }
// }

int         path(t_env *env)
{
    t_room  *room;
    t_pipe  *pipe;
    t_path  *path;
    char    **pathing;

    if (!(pathing = (char **)malloc(sizeof(char *) * 2)))
        return (FAILURE);
    pathing[1] = NULL;
    if (!(path = initpath()))
        return (FAILURE);
    room = env->room;
    pipe = env->pipe;
    while (room->state != END)
        room = room->next;
    return (SUCCESS);
    // path = init_path(env, room, pipe);
}
