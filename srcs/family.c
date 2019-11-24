# include "lem-in.h"

static t_room		*find_room(t_env *env, char *str)
{
	t_room			*room;

	room = env->room;
	while (ft_strcmp(room->name, str) != 0)
		room = room->next;
	return (room);
}

static	size_t		DfS(t_family *child)
{
	size_t	res;

	res = 0;
	while (child->parent->state != START)
	{
		child = child->parent;
		res++;
	}
	return (res);
}

static int			isnotparent(t_family *parent, char *str)
{
	if (parent->parent)
	{
		if (ft_strcmp(parent->parent->name, str) == 0)
			return (FALSE);
	}
	return (TRUE);
}
static	int			make_child(t_family *parent, t_room *tmp)
{
	t_family	*child;

	if (parent->child)
	{
		child = parent->child;
		if (child->bro)
		{
			while (child->bro != NULL)
				child = child->bro;
			if (!(child->bro = initfamily(tmp)))
				return (FAILURE);
			child->bro->parent = parent;
		}
		else
		{
			if (!(child->bro = initfamily(tmp)))
				return (FAILURE);
			child->bro->parent = parent;
		}
	}
	else
	{
		if (!(parent->child = initfamily(tmp)))
			return (FAILURE);
		parent->child->parent = parent;
	}
	return (SUCCESS);
}

static	int			make_family(t_env *env, t_family *parent, t_room *room)
{
	t_room			*tmp;
	t_pipe			*pipe;

	pipe = env->pipe;
	while (pipe)
	{
		if (ft_strcmp(pipe->a, room->name) == 0 && isnotparent(parent, pipe->b) == TRUE)
		{
			tmp = find_room(env, pipe->b);
			if (room->state == END)
				return (SUCCESS);
			if (make_child(parent, tmp) == FAILURE)
				return (FAILURE);
		}
		if (ft_strcmp(pipe->b, room->name) == 0 && isnotparent(parent, pipe->a) == TRUE)
		{
			tmp = find_room(env, pipe->a);
			if (room->state == END)
				return (SUCCESS);
			if (make_child(parent, tmp) == FAILURE)
				return (FAILURE);
		}
		pipe = pipe->next;
	}
	if (parent->child)
	{
		printf("parent = %s\n", parent->child->parent->name);
		printf("child = %s\n", parent->child->name);
	}
	if (parent->child->bro)
	{
		printf("child 2 = %s\n", parent->child->bro->name);
	}
	return (SUCCESS);
}

// static void 		print_family(t_family *parent)
// {
// 	while (parent)
// 	{
// 		if (parent->bro)
// 			print_family(parent->bro);
// 		printf("%s\n", parent->name);
// 		if (parent->child)
// 			parent = parent->child;
// 		else
// 			break ;
// 	}
// }

int					family(t_env *env)
{
	t_family		*parent;
	t_family		*bro;
	t_room			*room;
	t_room			*broroom;

	room = env->room;
	while (room->state != START)
		room = room->next;
	parent = initfamily(room);
	env->family = parent;
	if (make_family(env, parent, room) == FAILURE)
		return (FAILURE);
	while (parent->child)
	{
		parent = parent->child;
		room = parent->origin;
		printf("distance from start = %zu\n", DfS(parent));
		if (make_family(env, parent, room) == FAILURE)
			return (FAILURE);
		if (parent->bro)
		{
			bro = parent->bro;
			broroom = bro->origin;
			printf("distance from start = %zu\n", DfS(parent));
			if (make_family(env, bro, broroom) == FAILURE)
				return (FAILURE);
			if (bro->child)
			{
				bro = bro->child;
				broroom = bro->origin;
				if (make_family(env, bro, broroom) == FAILURE)
					return (FAILURE);
			}
		}
	}
	// print_family(env->family);
	return (SUCCESS);
}
