#include "lem-in.h"

// static void     find_pos(t_pipe *pipe, t_room *a, t_room *b)
// {
//     size_t      **result;
//     size_t      **pos;
//     size_t      i;
//
//     result = (size_t **)malloc(sizeof(size_t *) * pipe->size);
//     pos = (size_t **)malloc(sizeof(size_t *) * 2);
//     pos[A] = (size_t *)malloc(sizeof(size_t) * 2);
//     pos[B] = (size_t *)malloc(sizeof(size_t) * 2);
//     pos[A][X] = a->x;
//     pos[A][Y] = a->y;
//     pos[B][X] = b->x;
//     pos[B][Y] = b->y;
//     pipe->pos = pos;
//     pipe->result = result;
//     i = 0;
//     while (i != pipe->size)
//     {
//         pipe->result[i] = (size_t *)malloc(sizeof(size_t) * 2);
//         closest_path(pipe, pos, i);
//         i++;
//     }
// }

// static void     find_connected_rooms(t_pipe *pipe, t_room *room)
// {
//     t_room  *a;
//     t_room  *b;
//
//     while (room)
//     {
//         if (ft_strcmp(pipe->a, room->name) == 0)
//             a = room;
//         if (ft_strcmp(pipe->b, room->name) == 0)
//             b = room;
//         room = room->next;
//     }
//     pipe->size = absolute((absolute(a->x - b->x) - absolute(a->y - b->y)) / 2);
//     if (pipe->size == 0)
//         pipe->size = 1;
//     // find_pos(pipe, a, b);
// }
//
// void            connect_pipes(t_env *env)
// {
//     t_room  *room;
//     t_pipe  *pipe;
//
//     room = env->room;
//     pipe = env->pipe;
//     while (pipe)
//     {
//         find_connected_rooms(pipe, room);
//         pipe = pipe->next;
//     }
// }
