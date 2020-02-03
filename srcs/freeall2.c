/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeall2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artprevo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 21:24:07 by artprevo          #+#    #+#             */
/*   Updated: 2020/01/07 14:30:16 by artprevo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void			freeants(t_env *env)
{
	t_ants		*ants;
	t_ants		*tmpa;

	if (env->ants_list)
	{
		ants = env->ants_list;
		while (ants)
		{
			tmpa = ants->next;
			free(ants);
			ants = tmpa;
		}
	}
}

void			freepipe(t_env *env)
{
	t_pipe	*pipe;
	t_pipe	*tmpp;

	if (env->pipe)
	{
		pipe = env->pipe;
		while (pipe)
		{
			tmpp = pipe->next;
			free(pipe);
			pipe = tmpp;
		}
	}
}
