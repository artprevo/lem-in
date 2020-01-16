/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeall.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artprevo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 21:24:07 by artprevo          #+#    #+#             */
/*   Updated: 2020/01/07 14:30:16 by artprevo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static	void	freeanswer(t_env *env)
{
	t_answer	*answer;
	t_answer	*tmpw;
	t_ants		*ants;
	t_ants		*tmpa;

	if (env->answer)
	{
		answer = env->answer;
		while (answer)
		{
			free(answer->path);
 			tmpw = answer->next;
			free(answer);
			answer = tmpw;
		}
	}
	if (env->ants_list)
	{
		ants = env->ants_list;
		while (ants)
		{
			tmpa = ants->next;
			free(ants);
			ants = tmpa;
		}
	}
}

static	void	freepath(t_env *env)
{
	t_path	*path;
	t_path	*tmpp;
	t_ways	*ways;
	t_ways	*tmpw;

	if (env->path)
	{
		path = env->path;
		while (path)
		{
			ways = path->ways;
			while (ways)
			{
				tmpw = ways->next;
				free(ways);
				ways = tmpw;
			}
			tmpp = path->next;
			free(path);
			path = tmpp;
		}
	}
}

static	void	freepipe(t_env *env)
{
	t_pipe	*pipe;
	t_pipe	*tmpp;
	t_room	*room;
	t_room	*tmpr;

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
	if (env->room)
	{
		room = env->room;
		while (room)
		{
			free(room->name);
			tmpr = room->next;
			free(room);
			room = tmpr;
		}
	}
}

static	void	freematrice(t_env *env)
{
	size_t	i;
	size_t	**matrice;

	if (env->matrice)
	{
		matrice = env->matrice;
		i = 0;
		while (i <= env->idmax + 1)
		{
			free(matrice[i]);
			i++;
		}
		free(env->matrice);
	}
	i = 0;
	if (env->answer_matrice)
	{
		matrice = env->answer_matrice;
		while (i <= env->path_idmax + 1)
		{
			free(matrice[i]);
			i++;
		}
		free(env->answer_matrice);
	}
}

void			tafreetatoucompri(t_env *env)
{
	freematrice(env);
	freepipe(env);
	freepath(env);
	freeanswer(env);
	free(env);
}
