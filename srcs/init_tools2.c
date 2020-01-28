/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tools2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artprevo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 18:06:40 by artprevo          #+#    #+#             */
/*   Updated: 2020/01/11 18:06:51 by artprevo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_answer			*create_answer(t_env *env)
{
	t_answer	*new;
	t_answer	*tmp;

	if (env->answer == NULL)
	{
		if (!(new = initanswer()))
			return (NULL);
		env->answer = new;
	}
	else
	{
		if (!(new = initanswer()))
			return (NULL);
		tmp = env->answer;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->next = NULL;
	}
	return (new);
}

t_ants				*create_ants(t_env *env, t_path *path, size_t id)
{
	t_ants	*new;
	t_ants	*tmp;

	if (env->ants_list == NULL)
	{
		if (!(new = initants(path, id)))
			return (NULL);
		env->ants_list = new;
	}
	else
	{
		if (!(new = initants(path, id)))
			return (NULL);
		tmp = env->ants_list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->next = NULL;
	}
	return (new);
}
