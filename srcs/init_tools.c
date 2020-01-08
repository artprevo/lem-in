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
		new = initways(id);
		path->ways = new;
	}
	else
	{
		new = initways(id);
		tmp = path->ways;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->next = NULL;
	}
	return (new);
}

t_answer			*create_answer(t_env *env)
{
	t_answer	*new;
	t_answer	*tmp;

	if (env->answer == NULL)
	{
		new = initanswer();
		env->answer = new;
	}
	else
	{
		new = initanswer();
		tmp = env->answer;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->next = NULL;
	}
	return (new);
}

t_ants			*create_ants(t_env *env, t_path *path, size_t id)
{
	t_ants	*new;
	t_ants	*tmp;

	if (env->ants_list == NULL)
	{
		new = initants(path, id);
		env->ants_list = new;
	}
	else
	{
		new = initants(path, id);
		tmp = env->ants_list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->next = NULL;
	}
	return (new);
}
