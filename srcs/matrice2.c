/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrice2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artprevo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 18:12:50 by artprevo          #+#    #+#             */
/*   Updated: 2020/01/11 18:12:58 by artprevo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void	clean_matrice(t_env *env, size_t **matrice)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i <= env->idmax)
	{
		j = 0;
		while (j <= env->idmax)
		{
			if (matrice[i][j] == 2 || matrice[i][j] == 3)
				matrice[i][j] = 1;
			j++;
		}
		i++;
	}
	env->matrice = matrice;
}

void		okazou(t_env *env)
{
	size_t	**matrice;
	size_t	j;

	clean_matrice(env, env->matrice);
	matrice = env->matrice;
	if (matrice[0][env->idmax] == 1)
	{
		matrice[0][env->idmax] = 2;
		make_path(env);
		matrice[0][env->idmax] = 1;
	}
	j = 0;
	while (j <= env->idmax)
	{
		if (matrice[0][j] == 1 && matrice[env->idmax][j] == 1)
		{
			matrice[0][j] = 2;
			matrice[j][env->idmax] = 2;
			make_path(env);
		}
		j++;
	}
	clean_matrice(env, env->matrice);
}

static int	scout_matrice(t_env *env, size_t **matrice, size_t *i, size_t *j)
{
	matrice[*i][*j] = 2;
	if (*j == env->idmax)
	{
		if (make_path(env) == FAILURE)
			return (FAILURE);
		recursive(env, matrice, env->idmax);
		*j = *i;
		*i = recursive(env, matrice, *i);
	}
	else if (*i != env->idmax)
	{
		*i = *j;
		*j = -1;
	}
	return (SUCCESS);
}

int			explore_matrice(t_env *env, size_t i, size_t j, size_t **matrice)
{
	size_t	z;

	z = 0;
	printf("Timer = %llu ms, %s\n", g_timer, "Algo_start");
	while (j <= env->idmax)
	{
		if (matrice[i][j] == 1 && (did_not_pass(env, matrice[j]) == TRUE))
		{
			if (scout_matrice(env, matrice, &i, &j) == FAILURE)
				return (FAILURE);
		}
		else if (j == env->idmax && i != env->idmax)
		{
			j = i;
			i = recursive(env, matrice, i);
			matrice[i][j] = 3;
		}
		j++;
		if (j == env->idmax && i == 0)
			return (SUCCESS);
	}
	return (SUCCESS);
}
