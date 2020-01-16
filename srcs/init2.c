/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artprevo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 18:03:47 by artprevo          #+#    #+#             */
/*   Updated: 2020/01/11 18:03:47 by artprevo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_ways				*initways(size_t id)
{
	t_ways	*new;

	if (!(new = (t_ways *)malloc(sizeof(t_ways))))
		return (NULL);
	new->ants = 0;
	new->id = id;
	new->next = NULL;
	return (new);
}

t_path				*initpath(void)
{
	t_path	*new;

	if (!(new = (t_path *)malloc(sizeof(t_path))))
		return (NULL);
	new->ways = NULL;
	new->next = NULL;
	new->turns = 0;
	return (new);
}

t_answer			*initanswer(void)
{
	t_answer	*new;

	if (!(new = (t_answer *)malloc(sizeof(t_answer))))
		return (NULL);
	new->path = NULL;
	new->best = 0;
	new->nb_path = 0;
	new->steps = 0;
	new->next = NULL;
	return (new);
}

t_ants				*initants(t_path *path, size_t id)
{
	t_ants	*new;

	if (!(new = (t_ants *)malloc(sizeof(t_ants))))
		return (NULL);
	new->id = id;
	new->path = path;
	new->arrived = 0;
	new->next = NULL;
	return (new);
}
