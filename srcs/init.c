/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artprevo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/12 19:02:43 by artprevo          #+#    #+#             */
/*   Updated: 2020/01/07 14:30:19 by artprevo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_pipe				*initpipe(void)
{
	t_pipe		*new;
	// static int i = 0;

	if (!(new = (t_pipe *)malloc(sizeof(t_pipe))))
		return (NULL);
	// printf("Static initpipe = %d\n", i++);
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
	// static int i = 0;

	if (!(new = (t_room *)malloc(sizeof(t_room))))
		return (NULL);
	new->state = 0;
	// printf("Static initroom = %d\n", i++);
	new->id = 0;
	new->name = NULL;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

static t_env		*ft_initenv(void)
{
	t_env	*new;
	// static int i = 0;

	if (!(new = (t_env *)malloc(sizeof(t_env))))
		return (NULL);
	new->matrice = NULL;
	new->answer_matrice = NULL;
	// printf("Static initenv = %d\n", i++);
	new->pipe = NULL;
	new->room = NULL;
	new->path = NULL;
	new->answer = NULL;
	new->ants_list = NULL;
	new->ants = 0;
	new->parsing_state = -1;
	new->nb_paths_used = 0;
	new->idmax = 0;
	new->path_idmax = 0;
	new->turns = 0;
	new->steps = 0;
	new->resolution = 0;
	return (new);
}

t_env				*processinit(void)
{
	t_env	*new;

	new = ft_initenv();
	return (new);
}
