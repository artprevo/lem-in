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

t_answer	*find_best_answer(t_env *env)
{
	t_answer	*answer;
	t_answer	*best;
	size_t		score;
	size_t		score2;

	answer = env->answer;
	score = ((answer->steps / answer->nb_path) +
	(answer->steps % answer->nb_path) + (env->ants / answer->nb_path) +
	(env->ants % answer->nb_path));
	while (answer)
	{
		score2 = ((answer->steps / answer->nb_path) +
		(answer->steps % answer->nb_path) + (env->ants / answer->nb_path) +
		(env->ants % answer->nb_path));
		if (score2 <= score)
		{
			best = answer;
			score = score2;
		}
		answer = answer->next;
	}
	return (best);
}

// delete de env->ants % answer->nb_path car ca faisait un faux resultat;
void		reso_calcul(t_env *env, t_path *tmp, t_answer *answer)
{
	// printf("steps du straight = %zu\n", tmp->steps + env->ants);
	// printf("steps de l'answer = %zu \n", (((answer->steps / answer->nb_path) +
	// (answer->steps % answer->nb_path)) +
	// (env->ants / answer->nb_path)));
	// printf("steps / path = %zu\n", ((answer->steps / answer->nb_path) +
	// (answer->steps % answer->nb_path)));
	// printf("ants / nb_path = %zu\n", (env->ants / answer->nb_path));
	if ((tmp->steps + env->ants) < (((answer->steps / answer->nb_path) +
	(answer->steps % answer->nb_path)) + (env->ants / answer->nb_path)))
	{
		env->steps = (tmp->steps + env->ants);
		env->nb_paths_used = 1;
		env->resolution = STRAIGHT;
	}
	else
	{
		env->steps = (((answer->steps / answer->nb_path) +
		(answer->steps % answer->nb_path)) + (env->ants / answer->nb_path)
	+ env->ants % answer->nb_path);
		env->resolution = MULTIPATH;
		env->answer = answer;
		env->nb_paths_used = answer->nb_path;
	}
}

size_t		*add_path(t_env *env, size_t **matrice, size_t k, size_t i)
{
	size_t		j;
	size_t		*paths;

	if (!(paths = (size_t *)malloc(sizeof(size_t) * (k + 1))))
		return (NULL);
	// printf("taille malloc = %zu\n", k + 1);
	j = 0;
	k = 0;
	paths[0] = i;
	// printmatrice2(env);
	// printf("i = %zu || j = %zu || k = %zu\n", i, j, k);
	while (j <= env->path_idmax)
	{
		if (matrice[i][j] == 2)
			paths[++k] = j;
		// printf("paths[k] = %zu || k = %zu\n", paths[k], k);
		// printf("i = %zu || j = %zu || k = %zu\n", i, j, k);
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
