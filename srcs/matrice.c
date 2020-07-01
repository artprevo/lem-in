/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrice.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artprevo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 14:30:31 by artprevo          #+#    #+#             */
/*   Updated: 2020/01/07 14:30:32 by artprevo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		did_not_pass(t_env *env, int *line)
{
	int i;
	int k;

	i = 0;
	k = 0;
	while (i <= env->idmax)
	{
		if (line[i] == 2)
			k++;
		i++;
	}
	if (k > 0)
		return (FALSE);
	return (TRUE);
}

int			fill_ways(t_env *env, t_path *path, int **matrice, int steps)
{
	int	i;
	int	j;

	if (!(create_ways(path, 0)))
		return (FAILURE);
	i = 0;
	while (i <= env->idmax)
	{
		j = 0;
		while (j <= env->idmax)
		{
			if (matrice[i][j] == 2)
			{
				steps++;
				if (!(create_ways(path, j)))
					return (FAILURE);
				i = j;
				j = -1;
			}
			j++;
		}
		i++;
	}
	path->steps = steps;
	return (SUCCESS);
}

int			make_path(t_env *env)
{
	t_path	*path;
	int	**matrice;

	if (!(path = create_path(env)))
		return (FAILURE);
	matrice = env->matrice;
	if (fill_ways(env, path, matrice, 0) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int		recursive(t_env *env, int **matrice, int i)
{
	int	k;

	k = 0;
	while (k != env->idmax)
	{
		if (matrice[k][i] == 2)
		{
			matrice[k][i] = 1;
			return (k);
		}
		k++;
	}
	return (i);
}

int			set_matrice(t_env *env)
{
	int	**matrice;
	int	i;
	t_pipe	*pipe;

	printf("Timer = %llu ms, %s\n", g_timer, "Start set_matrice");
	if (!(matrice = (int **)malloc(sizeof(int *) * (env->idmax + 1))))
		return (FAILURE);
	i = 0;
	while (i < env->idmax + 1)
	{
		if (!(matrice[i] = (int *)malloc(sizeof(int) * (env->idmax + 1))))
			return (FAILURE);
		i++;
	}
	// matrice[i] = NULL;
	pipe = env->pipe;
	while (pipe)
	{
		matrice[pipe->ida][pipe->idb] = 1;
		matrice[pipe->idb][pipe->ida] = 1;
		pipe = pipe->next;
	}
	env->matrice = matrice;
	if (explore_matrice(env, 0, 0, matrice) == FAILURE)
		return (FAILURE);
	printf("Timer = %llu ms, %s\n", g_timer, "End set_matrice");
	// printmatrice(env);
	return (SUCCESS);
}
