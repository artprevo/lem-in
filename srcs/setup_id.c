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

#include "lemin.h"

void			put_id_path(t_env *env)
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
	t_room	*room;
	t_room	*tmp;

	printf("env->idmax = %zu\n", env->idmax);
	env->idmax--;
	room = env->room;
	while (room)
	{
		if (room->state == START && room->id != 0)
		{
			tmp = env->room;
			while (tmp && tmp->id != 0)
				tmp = tmp->next;
			tmp->id = room->id;
			room->id = 0;
		}
		else if (room->state == END && room->id != env->idmax)
		{
			tmp = env->room;
			while (tmp && tmp->id != env->idmax)
				tmp = tmp->next;
			tmp->id = room->id;
			room->id = env->idmax;
		}
		room = room->next;
	}
}
