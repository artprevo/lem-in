# include "lem-in.h"

static void 	print_answer(t_env *env, size_t ants, size_t idroom)
{
    t_room  *room;

    room = env->room;
    while (room->id != idroom)
        room = room->next;
	ft_putchar('L');
	ft_putnbr((int)ants);
	ft_putchar('-');
	ft_putstr(room->name);
}

static int  ants_multipath(t_env *env)
{
    t_answer    *answer;
    size_t      k;
    size_t      id;
    t_ants      *ants;

    id = 1;
    k = 0;
    answer = env->answer;
    while (id <= env->ants)
    {
        if (k >= answer->nb_path)
            k = 0;
        printf("path = %zu\n", answer->path[k]);
        ants = create_ants(env, find_path(answer->path[k], env), id);
        printf("ants->id = %zu\n", ants->id);
        k++;
        id++;
    }
    return (SUCCESS);
}

static int  multipathing(t_env *env)
{
    t_ants      *ants;
    t_answer    *answer;
    t_ways      *ways;
    size_t      i;

    ants = env->ants_list;
    answer = env->answer;
    while (env->turns <= env->steps - env->nb_paths_used)
    {
        i = 0;
        ants = env->ants_list;
        while (ants && i < answer->nb_path)
        {
            if (ants->arrived == 0)
            {
                ways = ants->path->ways;
                while (ways && ways->ants != ants->id)
                    ways = ways->next;
                if (!ways)
                    ways = ants->path->ways;
                if (ways->id != 0 && ways->id != env->idmax)
                {
                    ways->ants = 0;
                    ways = ways->next;
                    if (ways->id == env->idmax)
                        ants->arrived = 1;
                    print_answer(env, ants->id, ways->id);
                    ft_putstr(" ");
                    ways->ants = ants->id;
                }
                else if (ways->id == 0)
                {
                    ways = ways->next;
                    print_answer(env, ants->id, ways->id);
                    ft_putstr(" ");
                    ways->ants = ants->id;
                    i++;
                }
            }
            ants = ants->next;
        }
        ft_putchar('\n');
        env->turns++;
    }
    return (SUCCESS);
}

int         print_result(t_env *env)
{
    size_t      id;
    t_ants      *ants;
    t_path      *path;

    id = 1;
    path = env->path;
    if (env->resolution == 1)
    {
        while ((path->steps + env->ants) != env->steps)
            path = path->next;
        while (id <= env->ants)
        {
            ants = create_ants(env, path, id);
            printf("ants->id = %zu\n", ants->id);
            id++;
        }
        if (multipathing(env) == FAILURE)
            return (FAILURE);
    }
    else
    {
        if (ants_multipath(env) == FAILURE)
            return (FAILURE);
        if (multipathing(env) == FAILURE)
            return (FAILURE);
    }
    printf("steps = %zu\n", env->steps);
    printf("nb_paths_used = %zu\n", env->nb_paths_used);
    printf("turns = %zu\n", env->turns);
    return (SUCCESS);
}
