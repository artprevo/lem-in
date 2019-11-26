/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeall.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artprevo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 21:24:07 by artprevo          #+#    #+#             */
/*   Updated: 2019/10/18 16:17:21 by artprevo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

static	void	freepipe(t_env *env)
{
	t_pipe	*pipe;
	t_pipe	*tmpp;

	if (env->pipe)
	{
		pipe = env->pipe;
		while (pipe)
		{
			free(pipe->a);
			free(pipe->b);
			tmpp = pipe->next;
			free(pipe);
			pipe = tmpp;
		}
	}
}

static	void	freeroom(t_env *env)
{
	t_room	*room;
	t_room	*tmpp;

	if (env->room)
	{
		room = env->room;
		while (room)
		{
			free(room->name);
			tmpp = room->next;
			free(room);
			room = tmpp;
		}
	}
}

void			tafreetatoucompri(t_env *env)
{
	freepipe(env);
	freeroom(env);
	free(env);
}
