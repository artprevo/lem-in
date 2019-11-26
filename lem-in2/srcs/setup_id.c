# include "lem-in.h"

static void 	for_the_test(t_env *env)
{
	t_room		*room;

	room = env->room;
	while (room)
	{
		if (room->state != END && room->state != START)
			room->id = ft_atoi(room->name);
		room = room->next;
	}
}

static void 	true_end(t_env *env)
{
	// size_t		tmp;
	t_room		*room;
	t_room		*end;

	room = env->room;
	end = env->room;
	while (end->state != END)
		end = end->next;
	// while (room->id != env->idmax)
	// 	room = room->next;
	// tmp = end->id;
	// end->id = room->id;
	// room->id = tmp;
	end->id = env->idmax;
}

static void 	put_id_pipe(t_env *env)
{
	t_pipe	*pipe;
	t_room	*room;

	room = env->room;
	pipe = env->pipe;
	while (pipe)
	{
		room = env->room;
		while (room)
		{
			if (ft_strcmp(room->name, pipe->a) == 0)
				pipe->ida = room->id;
			if (ft_strcmp(room->name, pipe->b) == 0)
				pipe->idb = room->id;
			room = room->next;
		}
		pipe = pipe->next;
	}
}

void			put_id_room(t_env *env)
{
	size_t	id;
	t_room	*room;

	room = env->room;
	id = 1;
	while (room)
	{
		if (room->state == START)
			room->id = 0;
		else
		{
			room->id = id;
			id++;
		}
		room = room->next;
	}
	env->idmax = id - 1;
	true_end(env);
	for_the_test(env);
	put_id_pipe(env);
	// printpipe(env);
	// printroom(env);
}
