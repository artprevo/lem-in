/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   answer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artprevo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 14:29:53 by artprevo          #+#    #+#             */
/*   Updated: 2020/01/07 14:29:56 by artprevo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

static int		make_answer(t_env *env, size_t i, size_t k)
{
	t_answer	*answer;
	size_t		**matrice;
	t_path		*path;

	if (!(answer = create_answer(env)))
		return (FAILURE);
	matrice = env->answer_matrice;
	answer->nb_path = k + 1;
	if (!(answer->path = add_path(env, matrice, k, i)))
		return (FAILURE);
	i = 0;
	while (i < answer->nb_path)
	{
		path = env->path;
		while (path->id != answer->path[i])
			path = path->next;
		answer->steps += path->steps;
		i++;
	}
	if (env->steps == 0 || answer->steps < env->steps)
	{
		env->steps = answer->steps;
		answer->best = 1;
	}
	return (SUCCESS);
}

static int		explore_answer_matrice(t_env *env)
{
	size_t		**matrice;
	size_t		i;
	size_t		j;
	size_t		k;

	matrice = env->answer_matrice;
	i = 0;
	while (i <= env->path_idmax)
	{
		j = 0;
		k = 0;
		while (j <= env->path_idmax)
		{
			if (matrice[i][j] == 1)
				k++;
			j++;
		}
		if (k != 0)
		{
			if (make_answer(env, i, k) == FAILURE)
				return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}

static void		find_nb_path(t_env *env)
{
	size_t		i;
	size_t		j;
	size_t		nb_paths_used;
	size_t		**matrice;

	matrice = env->matrice;
	nb_paths_used = 0;
	i = 0;
	j = 0;
	while (j <= env->idmax)
	{
		if (matrice[0][j] == 1)
			i++;
		j++;
	}
	j = 0;
	while (j <= env->idmax)
	{
		if (matrice[env->idmax][j] == 1)
			nb_paths_used++;
		j++;
	}
	env->nb_paths_used = (i <= nb_paths_used ? i : nb_paths_used);
}

static	void	set_resolution(t_env *env)
{
	t_path		*path;
	t_path		*tmp;
	t_answer	*answer;

	path = env->path;
	while (path)
	{
		if (!tmp || path->steps < tmp->steps)
			tmp = path;
		path = path->next;
	}
	answer = env->answer;
	while (answer)
	{
		if (answer->best == 1)
			break ;
		answer = answer->next;
	}
	reso_calcul(env, tmp, answer);
}

int				find_turns(t_env *env)
{
	find_nb_path(env);
	put_id_path(env);
	set_answer_matrice(env);
	if (explore_answer_matrice(env) == FAILURE)
		return (FAILURE);
	set_resolution(env);
	return (SUCCESS);
}
