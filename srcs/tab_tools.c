// #include "lem-in.h"
//
// static    size_t   distance(size_t **pos)
// {
//     return(absolute(absolute(pos[A][X] - pos[B][X]) + absolute(pos[A][Y] - pos[B][Y])));
// }
//
// static void      closest_cell(size_t **pos)
// {
//     size_t  **tmp;
//     size_t  xorigin;
//     size_t  yorigin;
//
//     tmp = pos;
//     xorigin = pos[A][X];
//     yorigin = pos[A][Y];
//
//     tmp[A][X] = xorigin + UP;
//     if (distance(tmp) < distance(pos))
//         pos[A][X] = pos[A][X] + UP;
//     tmp[A][Y] = yorigin + LEFT;
//     if (distance(tmp) < distance(pos))
//         pos[A][Y] = yorigin + LEFT;
//     tmp[A][X] = xorigin;
//     if (distance(tmp) < distance(pos))
//         pos[A][X] = xorigin;
//     tmp[A][X] = xorigin + DOWN;
//     if (distance(tmp) < distance(pos))
//         pos[A][X] = xorigin + DOWN;
//     tmp[A][Y] = yorigin;
//     if (distance(tmp) < distance(pos))
//         pos[A][Y] = yorigin;
//     tmp[A][Y] = yorigin + RIGHT;
//     if (distance(tmp) < distance(pos))
//         pos[A][Y] = yorigin + RIGHT;
//     tmp[A][X] = xorigin;
//     if (distance(tmp) < distance(pos))
//         pos[A][X] = xorigin;
//     tmp[A][X] = xorigin + UP;
//     if (distance(tmp) < distance(pos))
//         pos[A][X] = xorigin + UP;
// }
//
// void       closest_path(t_pipe *pipe, size_t **pos, int i)
// {
//     printf("A |||| x = %zu || y = %zu\n", pos[0][0], pos[0][1]);
//     printf("B |||| x = %zu || y = %zu\n", pos[1][0], pos[1][1]);
//     printf("sizeofpipe = %zu\n", pipe->size);
//     printf("distance A to B = %zu\n", distance(pos));
//     closest_cell(pos);
//     pipe->result[i][X] = pos[A][X];
//     pipe->result[i][Y] = pos[A][Y];
//     printf("result = %zu, %zu\n", pipe->result[i][X], pipe->result[i][Y]);
// }
