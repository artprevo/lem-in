/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   result.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artprevo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 14:30:47 by artprevo          #+#    #+#             */
/*   Updated: 2020/01/07 14:30:49 by artprevo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void			print_answer(t_env *env, size_t ants, size_t idroom)
{
	t_room		*room;

	room = env->room;
	while (room->id != idroom)
		room = room->next;
	ft_putchar('L');
	ft_putnbr((int)ants);
	ft_putchar('-');
	ft_putstr(room->name);
}

static int		ants_multipath(t_env *env)
{
	t_answer	*answer;
	size_t		k;
	size_t		id;
	t_ants		*ants;

	id = 1;
	k = 0;
	answer = env->answer;
	while (id <= env->ants)
	{
		if (k >= answer->nb_path)
			k = 0;
		if (!(ants = create_ants(env, find_path(answer->path[k], env), id)))
			return (FAILURE);
		k++;
		id++;
	}
	return (SUCCESS);
}

static void		multipathing(t_env *env, size_t i, size_t space)
{
	t_ants		*ants;
	t_ways		*ways;

	while (everyone_not_arrived(env) == TRUE)
	{
		ants = mp_tool5(env, &i, &space);
		while (ants && i < env->nb_paths_used)
		{
			if (ants->arrived == 0)
			{
				env->wrote = 1;
				ways = mp_tool3(env, ants);
				if (ways->id != 0 && ways->id != env->idmax)
					ways = mp_tool1(env, ways, ants, space);
				else if (ways->id == 0 && ways->id != env->idmax)
				{
					ways = mp_tool2(env, ways, ants, space);
					i++;
				}
				space++;
			}
			ants = ants->next;
		}
		mp_tool4(env);
	}
}

int				print_result(t_env *env, size_t id)
{
	t_ants		*ants;
	t_path		*path;

	path = env->path;
	printf("entree print_result\n");
	printf("reso = %zu || nb_paths_usable = %zu || env->ants = %zu || env->steps = %zu\n", env->resolution, env->nb_paths_used, env->ants, env->steps);
	if (env->resolution == STRAIGHT)
	{
		while ((path->steps + env->ants) != env->steps)
			path = path->next;
		env->nb_paths_used = 1;
		while (id <= env->ants)
		{
			if (!(ants = create_ants(env, path, id)))
				return (FAILURE);
			id++;
		}
		multipathing(env, 0, 0);
	}
	else
	{
		if (ants_multipath(env) == FAILURE)
			return (FAILURE);
		multipathing(env, 0, 0);
	}
	return (SUCCESS);
}
