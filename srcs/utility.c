/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artprevo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 14:31:01 by artprevo          #+#    #+#             */
/*   Updated: 2020/01/07 14:31:02 by artprevo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

size_t		absolute(int i)
{
	if (i < 0)
		return (-i);
	return (i);
}

void		reso_calcul(t_env *env, t_path *tmp, t_answer *answer)
{
	if ((tmp->steps + env->ants) < (((answer->steps / answer->nb_path) +
	(answer->steps % answer->nb_path)) +
	(env->ants / answer->nb_path + env->ants % answer->nb_path)))
	{
		env->steps = (tmp->steps + env->ants);
		env->resolution = STRAIGHT;
	}
	else
	{
		env->steps = (((answer->steps / answer->nb_path) +
		(answer->steps % answer->nb_path)) +
		(env->ants / answer->nb_path + env->ants % answer->nb_path));
		env->resolution = MULTIPATH;
		env->answer = answer;
	}
}

size_t		*add_path(t_env *env, size_t **matrice, size_t k, size_t i)
{
	size_t		j;
	size_t		*paths;

	if (!(paths = (size_t *)malloc(sizeof(size_t) * (k + 2))))
		return (NULL);
	j = 0;
	k = 0;
	paths[0] = i;
	while (j <= env->path_idmax)
	{
		if (matrice[i][j] == 1)
			paths[++k] = j;
		j++;
	}
	return (paths);
}

t_path		*find_best_path(t_env *env)
{
	t_path		*path;
	t_path		*tmp;

	path = env->path;
	tmp = 0;
	while (path)
	{
		if (!tmp || path->steps < tmp->steps)
			tmp = path;
		path = path->next;
	}
	return (tmp);
}

int			everyone_not_arrived(t_env *env)
{
	t_ants *ants;

	ants = env->ants_list;
	while (ants)
	{
		if (ants->arrived == 0)
			return (TRUE);
		ants = ants->next;
	}
	return (FALSE);
}
