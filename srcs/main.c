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
	printf("Timer = %llu ms, %s\n", g_timer, "End of parsing");
	free(line);
	if (i != 0)
		ft_putchar('\n');
	return (SUCCESS);
}

static int			processtreatment(t_env *env)
{
	// put_id_room(env, 1);
	if (set_matrice(env) == FAILURE)
		return (FAILURE);
	okazou(env);
	printf("Timer = %llu ms, %s\n", g_timer, "Start of answer");
	if (find_turns(env) == FAILURE)
		return (FAILURE);
	printf("Timer = %llu ms, %s\n", g_timer, "End of answer / Start of Print");
	if (print_result(env, 1) == FAILURE)
		return (FAILURE);
	printf("Timer = %llu ms, %s\n", g_timer, "End of prog");
	return (SUCCESS);
}

void	*time_loop(void *arg)
{
	(void)arg;
	g_timer = 0;
	while (1)
	{
		g_timer += 1;
		usleep(1000);
	}
	return 0;
}

int					main(void)
{
	t_env *env;

	pthread_t	timethread;

	pthread_create(&(timethread), NULL, time_loop, &timethread);
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
	printpath(env);
	printanswer(env);
	printroom(env);
	// printpipe(env);
	// printmatrice(env);
	tafreetatoucompri(env);
	return (0);
}
