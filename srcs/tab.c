#include "lem-in.h"

static t_tab   *init_tab(t_env *env)
{
    t_tab   *tab;

    tab = (t_tab*)malloc(sizeof(t_tab));
    tab->xmax = 0;
    tab->ymax = 0;
    tab->map = NULL;
    env->tab = tab;
    return (tab);
}

static void    get_size_of_tab(t_env *env, t_tab *tab)
{
    t_room  *room;

    room = env->room;
    while (room)
    {
        if (room->x > tab->xmax)
            tab->xmax = room->x;
        if (room->y > tab->ymax)
            tab->ymax = room->y;
        room = room->next;
    }
}

static  char    **create_map(t_tab *tab)
{
    char    **map;
    int     y;
    int     x;

    x = 0;
    map = (char **)malloc(sizeof(char *) * (tab->xmax + 2));
    map[tab->xmax + 1] = NULL;
    while (map[x] != NULL)
    {
        map[x] = (char *)malloc(sizeof(char) * (tab->ymax + 2));
        map[x][tab->ymax + 1] = '\0';
        x++;
    }
    x = 0;
    while (map[x] != NULL)
    {
        y = 0;
        while (map[x][y] != '\0')
            map[x][y++] = ' ';
        x++;
    }
    return (map);
}

static  void    fill_map(t_env *env, char **map)
{
    t_room  *room;
    t_pipe  *pipe;

    room = env->room;
    pipe = env->pipe;
    while (room)
    {
        map[room->x][room->y] = room->state + 48;
        room = room->next;
    }
    // connect_pipes(env);
}

void            maketab(t_env *env)
{
    t_tab   *tab;
    char    **map;

    tab = init_tab(env);
    tab = env->tab;
    get_size_of_tab(env, tab);
    map = create_map(tab);
    fill_map(env, map);
    tab->map = map;
    printmap(map);
}
