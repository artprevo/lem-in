/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artprevo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 18:39:36 by artprevo          #+#    #+#             */
/*   Updated: 2020/01/07 14:30:22 by artprevo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_room			*create_room(t_env *env)
{
	t_room	*new;
	t_room	*tmp;

	if (env->room == NULL)
	{
		if (!(new = initroom()))
			return (NULL);
		env->room = new;
	}
	else
	{
		if (!(new = initroom()))
			return (NULL);
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
		if (!(new = initpipe()))
			return (NULL);
		env->pipe = new;
	}
	else
	{
		if (!(new = initpipe()))
			return (NULL);
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
		if (!(new = initpath()))
			return (NULL);
		env->path = new;
	}
	else
	{
		if (!(new = initpath()))
			return (NULL);
		tmp = env->path;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->next = NULL;
	}
	return (new);
}

t_ways			*create_ways(t_path *path, size_t id)
{
	t_ways	*new;
	t_ways	*tmp;

	if (path->ways == NULL)
	{
		if (!(new = initways(id)))
			return (NULL);
		path->ways = new;
	}
	else
	{
		if (!(new = initways(id)))
			return (NULL);
		tmp = path->ways;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->next = NULL;
	}
	return (new);
}
