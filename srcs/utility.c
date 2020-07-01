/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artprevo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 14:31:01 by artprevo          #+#    #+#             */
/*   Updated: 2020/07/01 20:08:09 by artprevo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_answer	*find_best_answer(t_env *env)
{
	t_answer	*answer;
	t_answer	*best;
	int		score;
	int		score2;

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
// 	printf("steps du straight = %d\n", tmp->steps + env->ants);
// 	printf("steps de l'answer = %d \n", (((answer->steps / answer->nb_path) +
// 	(answer->steps % answer->nb_path)) +
// 	(env->ants / answer->nb_path)));
// 	printf("steps / path = %d\n", ((answer->steps / answer->nb_path) +
// 	(answer->steps % answer->nb_path)));
// 	printf("ants / nb_path = %d\n", (env->ants / answer->nb_path));
	if ((tmp->steps + env->ants) < (((answer->steps / answer->nb_path) +
	(answer->steps % answer->nb_path)) + (env->ants / answer->nb_path)))
	{
		printf("straight\n");
		env->steps = (tmp->steps + env->ants);
		env->nb_paths_used = 1;
		env->resolution = STRAIGHT;
	}
	else
	{
		printf("multi\n");
		env->steps = (((answer->steps / answer->nb_path) +
		(answer->steps % answer->nb_path)) + (env->ants / answer->nb_path)
	+ env->ants % answer->nb_path);
		env->resolution = MULTIPATH;
		env->answer = answer;
		env->nb_paths_used = answer->nb_path;
	}
}

int		*add_path(t_env *env, t_pth *tab)
{
	int		j;
	int		i;
	int		*paths;

	if (!(paths = (int *)malloc(sizeof(int) * (tab->size))))
		return (NULL);
	// printf("taille malloc = %d\n", k + 1);
	j = 0;
	i = 0;
	while (i < tab->size)
	{
		paths[j] = tab->path[i];
		j++;
		i++;
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
