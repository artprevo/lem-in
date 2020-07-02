/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   answer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artprevo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 14:29:53 by artprevo          #+#    #+#             */
/*   Updated: 2020/07/01 20:03:41 by artprevo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int				*dupliq(int *tab, int size)
{
	int i;
	int *new;

	if (!(new =(int*)malloc(sizeof(int) * size)))
		return (NULL);
	i = 0;
	while (i < size)
	{
		new[i] = tab[i];
		i++;
	}
	i = 0;
	while (i < size)
	{
		printf("tab[i] = %d\n", new[i]);
		i++;
	}
	return (new);
}

t_answer		*make_answer(t_env *env)
{
	t_answer	*answer;

	if (!(answer = create_answer(env)))
		return (NULL);
	printf("size = %d || steps = %d\n", env->result_size, env->steps);
	answer->nb_path = env->result_size;
	answer->path = dupliq(env->result, env->result_size);
	answer->steps = env->steps;
	int i = 0;
	while (i < answer->nb_path)
	{
		printf("tab[i] = %d\n", answer->path[i]);
		i++;
	}
	return (answer);
}

static int		explore_answer_matrice(t_env *env)
{
	int		**matrice;
	int		i;
	int		j;
	int		k;

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
			if (store_paths(env, k + 1, i) == FAILURE)
				return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}

static void		find_nb_path(t_env *env)
{
	int		i;
	int		j;
	int		nb_paths_used;
	int		**matrice;

	matrice = env->matrice;
	nb_paths_used = 0;
	i = 0;
	j = 0;
	// printmatrice(env);
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
	// printf("nb_paths_usable = %d || i = %d\n", nb_paths_used, i);
	env->nb_paths_used = (i <= nb_paths_used ? i : nb_paths_used);
}

static	void	set_resolution(t_env *env)
{
	t_path		*tmp;
		
	tmp = find_best_path(env);
	if (env->score)
		reso_calcul(env, tmp, env->answer);
	else
	{
		env->resolution = STRAIGHT;
		env->steps = (tmp->steps + env->ants);
	}
}

int				find_turns(t_env *env)
{
	find_nb_path(env);
	put_id_path(env);
	if (!env->path)
		return (FAILURE);
	if (set_answer_matrice(env) == FAILURE)
		return (FAILURE);
	if (explore_answer_matrice(env) == FAILURE)
		return (FAILURE);
	if (env->score)
		env->answer = make_answer(env);
	set_resolution(env);
	return (SUCCESS);
}
