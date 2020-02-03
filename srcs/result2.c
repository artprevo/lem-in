/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   result2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artprevo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 19:04:52 by artprevo          #+#    #+#             */
/*   Updated: 2020/01/11 19:04:58 by artprevo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_ways		*mp_tool1(t_env *env, t_ways *ways, t_ants *ants, size_t space)
{
	ways->ants = 0;
	ways = ways->next;
	if (ways->id == env->idmax)
		ants->arrived = 1;
	// if (space != 0)
	// 	ft_putstr(" ");
	print_answer(env, ants->id, ways->id);
	ways->ants = ants->id;
	return (ways);
}

t_ways		*mp_tool2(t_env *env, t_ways *ways, t_ants *ants, size_t space)
{
	ways = ways->next;
	// if (space != 0)
	// 	ft_putstr(" ");
	print_answer(env, ants->id, ways->id);
	ways->ants = ants->id;
	if (ways->id == env->idmax)
		ants->arrived = 1;
	return (ways);
}

t_ways		*mp_tool3(t_env *env, t_ants *ants)
{
	t_ways *ways;

	ways = ants->path->ways;
	while (ways && ways->ants != ants->id)
		ways = ways->next;
	if (!ways)
		ways = ants->path->ways;
	env = 0;
	return (ways);
}

void		mp_tool4(t_env *env)
{
	// if (env->wrote != 0)
		// ft_putchar('\n');
}

t_ants		*mp_tool5(t_env *env, size_t *i, size_t *space)
{
	t_ants	*ants;

	*i = 0;
	*space = 0;
	env->wrote = 0;
	ants = env->ants_list;
	return (ants);
}
