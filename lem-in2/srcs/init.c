/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artprevo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/12 19:02:43 by artprevo          #+#    #+#             */
/*   Updated: 2019/10/18 17:43:41 by artprevo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

t_pipe			*initpipe(void)
{
	t_pipe		*new;

	if (!(new = (t_pipe *)malloc(sizeof(t_pipe))))
		return (NULL);
	new->used = FALSE;
	new->a = NULL;
	new->b = NULL;
	new->ida = 0;
	new->idb = 0;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_room				*initroom(void)
{
	t_room	*new;

	if (!(new = (t_room *)malloc(sizeof(t_room))))
		return (NULL);
	new->state = 0;
	new->id = 0;
	new->name = NULL;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

static t_env		*ft_initenv(void)
{
	t_env	*new;

	if (!(new = (t_env *)malloc(sizeof(t_env))))
		return (NULL);
	new->matrice = NULL;
	new->pipe = NULL;
	new->room = NULL;
	new->path = NULL;
	new->ants = 0;
	new->parsing_state = -1;
	new->idmax = 0;
	new->turns = 0;
	return (new);
}

t_env				*processinit(void)
{
	t_env	*new;

	new = ft_initenv();
	return (new);
}

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
	new->usable = FALSE;
	return (new);
}
