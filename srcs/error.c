/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artprevo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 16:39:49 by artprevo          #+#    #+#             */
/*   Updated: 2020/01/14 16:39:57 by artprevo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int			check_room_authencity(t_env *env)
{
	char	*name;
	t_room	*room;
	t_room	*tmp;

	room = env->room;
	while (room)
	{
		name = room->name;
		tmp = env->room;
		while (tmp)
		{
			if (tmp != room && ft_strcmp(name, tmp->name) == 0)
				return (FAILURE);
			tmp = tmp->next;
		}
		room = room->next;
	}
	return (SUCCESS);
}

static int			check_pipe_authencity(t_env *env)
{
	t_room	*room;
	t_pipe	*pipe;
	size_t	k;

	pipe = env->pipe;
	while (pipe)
	{
		k = 0;
		room = env->room;
		while (room)
		{
			if (ft_strcmp(pipe->a, room->name) == 0)
				k++;
			if (ft_strcmp(pipe->b, room->name) == 0)
				k++;
			room = room->next;
		}
		if (k != 2)
			return (FAILURE);
		pipe = pipe->next;
	}
	return (SUCCESS);
}

int					check_room(char *line)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == ' ')
			j++;
		if (line[i] != ' ' && ft_isalnum(line[i]) == 0)
			return (TRUE);
		i++;
	}
	return (j);
}

int					checklinerror(char *line)
{
	int		i;
	int		k;

	i = 0;
	k = 0;
	if (ft_strchr(line, '-') != FALSE)
	{
		while (line[i])
		{
			if (line[i] != '-' && ft_isalnum(line[i]) == 0)
				return (TRUE);
			i++;
		}
		k++;
	}
	else
	{
		if (check_room(line) == 2)
			k++;
		if (check_room(line) == TRUE)
			return (TRUE);
	}
	if (k == 0)
		return (TRUE);
	return (FALSE);
}

int					checkerror(t_env *env)
{
	t_room	*room;
	int		i;

	i = 0;
	room = env->room;
	while (room)
	{
		if (room->state == START || room->state == END)
			i++;
		room = room->next;
	}
	if (i != 2)
		return (FAILURE);
	printf("Timer = %llu ms, %s\n", g_timer, "Start Check room");
	if (check_room_authencity(env) == FAILURE)
		return (FAILURE);
	printf("Timer = %llu ms, %s\n", g_timer, "Start check pipe");
	if (check_pipe_authencity(env) == FAILURE)
		return (FAILURE);
	printf("Timer = %llu ms, %s\n", g_timer, "End of checks");
	return (SUCCESS);
}
