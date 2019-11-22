#include "lem-in.h"

t_room	*find_room(t_env *env, char *str)
{
	t_room	*room;

	room = env->room;
	while (ft_strcmp(room->name, str) != 0)
		room = room->next;
	return (room);
}

static int	dont_exist(char **tab, char *str)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (strcmp(tab[i], str) == 0)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

static char **add_path(char **tab, char *str)
{
	int 	i;
	char	**tmp;

	i = 0;
	while (tab[i])
		i++;
	if (!(tmp = (char **)malloc(sizeof(char *) * (i + 2))))
	   return (NULL);
	tmp[i + 1] = NULL;
	i = 0;
	printf("new = %s\n", str);
	while (tab[i])
	{
		tmp[i] = ft_strdup(tab[i]);
		i++;
	}
	tmp[i] = ft_strdup(str);
	i = 0;
	while (tmp[i])
	{
		printf("tmp[%d] = %s\n", i, tmp[i]);
		i++;
	}
	printf("\n");
	return (tmp);
}

static int	 multi_path(t_env *env, t_room *room, char *str)
{
	t_pipe	*pipe;
	t_path	*tmp;

	tmp = create_path(env, env->path->steps, env->path->pathing);
	pipe = env->pipe;
	while (pipe)
	{
		if ((ft_strcmp(pipe->a, room->name) == 0) && (dont_exist(tmp->pathing, pipe->b) == TRUE))
		{
			if ((ft_strcmp(pipe->b, str) == 0))
			{
			}
			else
			{
				tmp->steps++;
				tmp->pathing = add_path(tmp->pathing, pipe->b);
				room = find_room(env, pipe->b);
				if (room->state == START)
				{
					env->nb_path++;
					tmp->id = env->nb_path;
					return (SUCCESS);
				}
				while (pipe->prev)
					pipe = pipe->prev;
			}
		}
		if ((ft_strcmp(pipe->b, room->name) == 0) && (dont_exist(tmp->pathing, pipe->a) == TRUE))
		{
			if ((ft_strcmp(pipe->a, str) == 0))
			{
			}
			else
			{
				tmp->steps++;
				tmp->pathing = add_path(tmp->pathing, pipe->a);
				room = find_room(env, pipe->a);
				if (room->state == START)
				{
					env->nb_path++;
					tmp->id = env->nb_path;
					return (SUCCESS);
				}
				while (pipe->prev)
					pipe = pipe->prev;
			}
		}
		pipe = pipe->next;
	}
	return (FAILURE);
}

static int   first_path(t_env *env, t_room *room, t_path *path)
{
	t_pipe	*pipe;

	pipe = env->pipe;
    while (pipe)
    {
        if ((ft_strcmp(pipe->a, room->name) == 0) && (dont_exist(path->pathing, pipe->b) == TRUE))
        {
			path->steps++;
			path->pathing = add_path(path->pathing, pipe->b);
			room = find_room(env, pipe->b);
			if (room->state == START)
				return (SUCCESS);
			while (pipe->prev)
				pipe = pipe->prev;
        }
		if ((ft_strcmp(pipe->b, room->name) == 0) && (dont_exist(path->pathing, pipe->a) == TRUE))
		{
			path->steps++;
			path->pathing = add_path(path->pathing, pipe->a);
			room = find_room(env, pipe->a);
			if (room->state == START)
				return (SUCCESS);
			while (pipe->prev)
				pipe = pipe->prev;
		}
		pipe = pipe->next;
    }
	return (FAILURE);
}

static void clean_path (t_env *env)
{
	t_room *room;
	t_path *path;
	int		i;

	room = env->room;
	path = env->path;
	while (room->state != START)
		room = room->next;
	while (path)
	{
		i = 0;
		while (path->pathing[i])
			i++;
		i--;
		if ((ft_strcmp(path->pathing[i], room->name) != 0))
			path->steps = 0;
		path = path->next;
	}
}
//
// static size_t	id_number(t_env *env)
// {
// 	t_path *path;
// 	size_t result;
//
// 	result = 0;
// 	path = env->path;
// 	while (path)
// 	{
// 		if (result <= path->id)
// 			result = path->id;
// 		path = path->next;
// 	}
// 	return (result);
// }

int         path(t_env *env)
{
    t_room  *room;
    t_pipe  *pipe;
    t_path  *path;
	t_path	*tmp;
    char    **pathing;
	size_t 	i;
	size_t	j;

    if (!(pathing = (char **)malloc(sizeof(char *) * 2)))
        return (FAILURE);
    room = env->room;
    pipe = env->pipe;
    while (room->state != END)
        room = room->next;
	if (!(pathing[0] = (char *)malloc(sizeof(char) * ft_strlen(room->name) + 1)))
		return (FAILURE);
	pathing[0] = ft_strdup(room->name);
	pathing[1] = NULL;
	if (!(path = create_path(env, 0, pathing)))
		return (FAILURE);
	if (!(tmp = create_path(env, 0, pathing)))
		return (FAILURE);
    if (first_path(env, room, tmp) == FAILURE)
	 	return (FAILURE);
	tmp->id = 1;
	path = env->path;
	i = 1;
	while (i < 7)
	{
		printf("i = %zu\n", i);
		clean_path(env);
		j = 0;
		while (tmp->id != i)
			tmp = tmp->next;
		while (tmp->pathing[j])
		{
			if (tmp->steps != 0)
			{
			printf("ON SAMUSE\n");
			multi_path(env, room, tmp->pathing[j]);
			}
			j++;
		}
		i++;
	}
	while (path)
	{
		i = 0;
		while (path->pathing[i] && path->steps != 0)
		{
			if (path->id != 0)
				printf("path->pathing[%zu] = %s\n", i, path->pathing[i]);
			i++;
		}
		if (path->id != 0)
		{
			printf("steps = %zu\n", path->steps);
			printf("ID = %zu\n", path->id);
		}
		path = path->next;
	}
	printf("nb of path = %zu\n", env->nb_path);
	return (SUCCESS);
}
