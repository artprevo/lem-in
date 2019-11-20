/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artprevo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 18:39:36 by artprevo          #+#    #+#             */
/*   Updated: 2019/10/18 18:19:54 by artprevo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

t_room			*create_room(t_env *env)
{
	t_room	*new;
	t_room	*tmp;

	if (env->room == NULL)
	{
		new = initroom();
		env->room = new;
	}
	else
	{
		new = initroom();
		tmp = env->room;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
		new->next = NULL;
	}
	return (new);
}

t_pipe			*create_pipe(t_env *env)
{
	t_pipe	*new;
	t_pipe	*tmp;

	if (env->pipe == NULL)
	{
		new = initpipe();
		env->pipe = new;
	}
	else
	{
		new = initpipe();
		tmp = env->pipe;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
		new->next = NULL;
	}
	return (new);
}

t_path			*create_path(t_env *env)
{
	t_path	*new;
	t_path	*tmp;

	if (env->path == NULL)
	{
		new = initpath();
		env->path = new;
	}
	else
	{
		new = initpath();
		tmp = env->path;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
		new->next = NULL;
	}
	return (new);
}
