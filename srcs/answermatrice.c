/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   answermatrice.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artprevo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 14:30:03 by artprevo          #+#    #+#             */
/*   Updated: 2020/07/01 20:03:57 by artprevo         ###   ########.fr       */
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

static void			full_dns(t_env *env)
{
	int	**matrice;
	int	i;
	int	j;
	int	k;

	matrice = env->answer_matrice;
	i = 0;
	while (i <= env->path_idmax)
	{
		j = 0;
		while (j <= env->path_idmax)
		{
			if (matrice[i][j] == 1)
			{
				k = j + 1;
				while (k <= env->path_idmax)
				{
					if (do_not_share(env, find_path(j, env), find_path(k, env)) == FALSE)
						matrice[i][j] = 0;
					k++;
				}
			}
			j++;
		}
		i++;
	}
}

t_path				*find_path(int i, t_env *env)
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
	int	i;
	int	j;
	int	**matrice;

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
	int	**matrice;
	int	i;

	if (!(matrice = (int **)malloc(sizeof(int *) *
	(env->path_idmax + 1))))
		return (FAILURE);
	i = 0;
	while (i < env->path_idmax + 1)
	{
		if (!(matrice[i] = (int *)malloc(sizeof(int) *
		(env->path_idmax + 1))))
			return (FAILURE);
		i++;
	}
	env->answer_matrice = matrice;
	fill_matrice(env);
	// printf("full dns commence\n");
	full_dns(env);
	// printf("full dns termine\n");
	// printmatrice2(env);
	return (SUCCESS);
}
