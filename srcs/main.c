/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artprevo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 14:30:26 by artprevo          #+#    #+#             */
/*   Updated: 2020/01/13 21:21:22 by artprevo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int					processparsing(t_env *env)
{
	char	*line;

	line = NULL;
	while (get_next_line(0, &line) == TRUE)
	{
		if (checktype(env, line) == FAILURE)
			return (FAILURE);
		free(line);
	}
	if (checkerror(env) == FAILURE)
		return (FAILURE);
	put_id_room(env, 1);
	if (set_matrice(env) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

static int			processtreatment(t_env *env)
{
	if (find_turns(env) == FAILURE)
	{
		printf("findturns\n");
		return (FAILURE);
	}
	if (print_result(env, 1) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int					main(void)
{
	t_env *env;

	env = processinit();
	if (processparsing(env) == FAILURE || processtreatment(env) == FAILURE)
		ft_putstr("ERROR\n");
	tafreetatoucompri(env);
	return (0);
}
