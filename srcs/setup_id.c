/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_id.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artprevo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 14:30:53 by artprevo          #+#    #+#             */
/*   Updated: 2020/01/07 14:30:54 by artprevo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "lem-in.h"

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

void 			put_id_path(t_env *env)
{
	t_path	*path;
	size_t	i;

	i = 0;
	path = env->path;
	while (path)
	{
		path->id = i;
		path = path->next;
		i++;
	}
	env->path_idmax = i - 1;
}

void			put_id_room(t_env *env)
{
	size_t	id;
	t_room	*room;

	room = env->room;
	id = 1;
	while (room)
	{
		id++;
		room = room->next;
	}
	env->idmax = id - 2;
	room = env->room;
	id = 1;
	while (room)
	{
		if (room->state == START)
			room->id = 0;
		else if (room->state == END)
			room->id = env->idmax;
		else
		{
			room->id = id;
			id++;
		}
		room = room->next;
	}
	put_id_pipe(env);
	// room = env->room;
	// while (room)
	// {
	// 	printf("room id = %zu || room name = %s || state = %zu\n", room->id, room->name, room->state);
	// 	room = room->next;
	// }
}
