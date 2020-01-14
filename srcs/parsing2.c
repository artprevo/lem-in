/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artprevo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 16:45:04 by artprevo          #+#    #+#             */
/*   Updated: 2020/01/14 16:45:14 by artprevo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int			checktype2(t_env *env, char *line)
{
	if (env->parsing_state == ANTS)
	{
		if (ft_atoi(line) <= 0)
			return (FAILURE);
		env->ants = ft_atoi(line);
		env->parsing_state = NORMAL;
		return (SUCCESS);
	}
	if (ft_strcmp(line, "##start") == 0)
	{
		env->parsing_state = START;
		return (SUCCESS);
	}
	if (ft_strcmp(line, "##end") == 0)
	{
		env->parsing_state = END;
		return (SUCCESS);
	}
	return (FAILURE);
}