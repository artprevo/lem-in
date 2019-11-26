#include "lem-in.h"

static int        fill_pipe(t_pipe *pipe, int type, char *line, int i)
{
    char    *tmp;
    int     j;
    int     k;

    k = 0;
    j = i;
    while (line[i] != '-' && line[i] != '\0')
        i++;
    tmp = ft_strnew(i - j + 1);
    while (j != i)
        tmp[k++] = line[j++];
    tmp[k] = '\0';
    if (type == A)
        pipe->a = ft_strdup(tmp);
    if (type == B)
        pipe->b = ft_strdup(tmp);
    free(tmp);
    return (i);
}

static void        parsing_pipe(t_env *env, char *line)
{
    t_pipe  *pipe;
    int     type;
    int     i;

    type = 0;
    i = 0;
    pipe = create_pipe(env);
    while (type != 2)
    {
        if (type == A)
            i = fill_pipe(pipe, A, line, i);
        if (type == B)
            i = fill_pipe(pipe, B, line, i + 1);
        type++;
    }
    // printpipe(pipe);
}

static int        fill_room(t_room *room, int type, char *line, int i)
{
    char    *tmp;
    int     j;
    int     k;

    k = 0;
    j = i;
    while (line[i] != ' ' && line[i] != '\0')
        i++;
    tmp = ft_strnew(i - j + 1);
    while (j != i)
        tmp[k++] = line[j++];
    tmp[k] = '\0';
    if (type == NAME)
        room->name = ft_strdup(tmp);
    free(tmp);
    return (i);
}

static void        parsing_room(t_env *env, char *line)
{
    t_room  *room;
    int     type;
    int     i;

    type = 0;
    i = 0;
    room = create_room(env);
    while (type != 3)
    {
        if (type == NAME)
            i = fill_room(room, NAME, line, i);
        if (type == XROOM)
            i = fill_room(room, XROOM, line, i + 1);
        if (type == YROOM)
            i = fill_room(room, YROOM, line, i + 1);
        type++;
    }
    room->state = env->parsing_state;
    env->parsing_state = NORMAL;
    // printroom(room);
}

int         checktype(t_env *env, char *line)
{
    if (env->parsing_state == ANTS)
    {
        env->ants = ft_atoi(line);
        env->parsing_state = NORMAL;
        return (SUCCESS);
    }
    if (line[0] == '#' && line[1] == '#')
    {
        if (line[2] == 's')
            env->parsing_state = START;
        else if (line[2] == 'e')
            env->parsing_state = END;
        return (SUCCESS);
    }
    if (strchr(line, '-') != FALSE)
        env->parsing_state = PIPE;
    if (env->parsing_state == NORMAL)
        parsing_room(env, line);
    if (env->parsing_state == START)
        parsing_room(env, line);
    if (env->parsing_state == END)
        parsing_room(env, line);
    if (env->parsing_state == PIPE)
        parsing_pipe(env, line);
    return (SUCCESS);
}
