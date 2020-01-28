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
		{
			free(line);
			return (FAILURE);
		}
		if (line != 0 && ft_strcmp(line, "\n") > 0)
		{
			ft_putstr(line);
			ft_putchar('\n');
		}
		free(line);
	}
	free(line);
	ft_putchar('\n');
	if (checkerror(env) == FAILURE)
		return (FAILURE);
	put_id_room(env, 1);
	if (set_matrice(env) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

static int			processtreatment(t_env *env)
{
	okazou(env);
	if (find_turns(env) == FAILURE)
		return (FAILURE);
	if (print_result(env, 1) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int					main(void)
{
	t_env *env;

	env = processinit();
	if (processparsing(env) == FAILURE)
		ft_putstr("ERROR\n");
	else if (processtreatment(env) == FAILURE)
		ft_putstr("ERROR\n");
	tafreetatoucompri(env);
	return (0);
}
