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
	size_t	i;

	i = 0;
	line = NULL;
	while (get_next_line(0, &line) == TRUE)
	{
		i++;
		ft_putstr(line);
		ft_putchar('\n');
		if (checktype(env, line) == FAILURE)
		{
			ft_putchar('\n');
			free(line);
			return (FAILURE);
		}
		free(line);
	}
	free(line);
	if (i != 0)
		ft_putchar('\n');
	return (SUCCESS);
}

static int			processtreatment(t_env *env)
{
	put_id_room(env, 1);
	if (set_matrice(env) == FAILURE)
		return (FAILURE);
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

	if (!(env = processinit()))
		ft_putstr("ERROR\n");
	else
	{
		processparsing(env);
		if (checkerror(env) == FAILURE)
			ft_putstr("ERROR\n");
		else if (processtreatment(env) == FAILURE)
			ft_putstr("ERROR\n");
	}
	tafreetatoucompri(env);
	return (0);
}
