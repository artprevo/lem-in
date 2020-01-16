/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   answermatrice.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artprevo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 14:30:03 by artprevo          #+#    #+#             */
/*   Updated: 2020/01/07 14:30:13 by artprevo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int			do_not_share(t_env *env, t_path *path, t_path *tmp)
{
	t_ways	*ways;
	t_ways	*tmp_ways;

	if (tmp->id == path->id)
		return (FALSE);
	ways = path->ways;
	while (ways)
	{
		tmp_ways = tmp->ways;
		while (tmp_ways)
		{
			if (tmp_ways->id == ways->id && ways->id != env->idmax &&
			ways->id != 0)
				return (FALSE);
			if ((ways->id == env->idmax || ways->id == 0) && path->steps == 1)
				return (FALSE);
			tmp_ways = tmp_ways->next;
		}
		ways = ways->next;
	}
	return (TRUE);
}

t_path				*find_path(size_t i, t_env *env)
{
	t_path	*path;

	path = env->path;
	while (path)
	{
		if (path->id == i)
			return (path);
		path = path->next;
	}
	return (path);
}

static void			fill_matrice(t_env *env)
{
	size_t	i;
	size_t	j;
	size_t	**matrice;

	i = 0;
	matrice = env->answer_matrice;
	while (i <= env->path_idmax)
	{
		j = 0;
		while (j <= env->path_idmax)
		{
			if (do_not_share(env, find_path(i, env), find_path(j, env)) == TRUE)
				matrice[i][j] = 1;
			else
				matrice[i][j] = 0;
			j++;
		}
		i++;
	}
}

int					set_answer_matrice(t_env *env)
{
	size_t	**matrice;
	size_t	i;

	if (!(matrice = (size_t **)malloc(sizeof(size_t *) *
	(env->path_idmax + 2))))
		return (FAILURE);
	i = 0;
	while (i <= env->path_idmax + 1)
	{
		if (!(matrice[i] = (size_t *)malloc(sizeof(size_t) *
		(env->path_idmax + 1))))
			return (FAILURE);
		i++;
	}
	matrice[--i] = NULL;
	env->answer_matrice = matrice;
	fill_matrice(env);
	return (SUCCESS);
}
