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

static int	scout_matrice(t_env *env, size_t **matrice, size_t *i, size_t *j)
{
	matrice[*i][*j] = 2;
	if (*j == env->idmax)
	{
		if (make_path(env) == FAILURE)
			return (FAILURE);
		*i = recursive(env, matrice, env->idmax);
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
		}
		j++;
		if (j == env->idmax && i == 0 && z > 0)
			return (SUCCESS);
		if (z++ > 1000000)
			return (SUCCESS);
	}
	return (SUCCESS);
}
