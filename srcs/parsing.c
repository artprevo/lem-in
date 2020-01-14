/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artprevo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 14:30:37 by artprevo          #+#    #+#             */
/*   Updated: 2020/01/07 14:30:37 by artprevo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int		fill_pipe(t_pipe *pipe, int type, char *line, int i)
{
	char	*tmp;
	int		j;
	int		k;

	k = 0;
	j = i;
	while (line[i] != '-' && line[i] != '\0')
		i++;
	tmp = ft_strnew(i - j + 1);
	while (j != i)
		tmp[k++] = line[j++];
	tmp[k] = '\0';
	if (type == A)
		pipe->a = ft_strdup(tmp);
	if (type == B)
		pipe->b = ft_strdup(tmp);
	free(tmp);
	return (i);
}

static void		parsing_pipe(t_env *env, char *line)
{
	t_pipe	*pipe;
	int		type;
	int		i;

	type = 0;
	i = 0;
	pipe = create_pipe(env);
	while (type != 2)
	{
		if (type == A)
			i = fill_pipe(pipe, A, line, i);
		if (type == B)
			i = fill_pipe(pipe, B, line, i + 1);
		type++;
	}
}

static int		fill_room(t_room *room, int type, char *line, int i)
{
	char	*tmp;
	int		j;
	int		k;

	k = 0;
	j = i;
	while (line[i] != ' ' && line[i] != '\0')
		i++;
	tmp = ft_strnew(i - j + 1);
	while (j != i)
		tmp[k++] = line[j++];
	tmp[k] = '\0';
	if (type == NAME)
		room->name = ft_strdup(tmp);
	free(tmp);
	return (i);
}

static void		parsing_room(t_env *env, char *line)
{
	t_room		*room;
	int			type;
	int			i;

	type = 0;
	i = 0;
	room = create_room(env);
	while (type != 3)
	{
		if (type == NAME)
			i = fill_room(room, NAME, line, i);
		if (type == XROOM)
			i = fill_room(room, XROOM, line, i + 1);
		if (type == YROOM)
			i = fill_room(room, YROOM, line, i + 1);
		type++;
	}
	room->state = env->parsing_state;
	env->parsing_state = NORMAL;
}

int				checktype(t_env *env, char *line)
{
	if (checktype2(env, line) == SUCCESS)
		return (SUCCESS);
	if (checklinerror(line) == TRUE)
		return (SUCCESS);
	if (ft_strchr(line, '-') != FALSE)
	{
		parsing_pipe(env, line);
		return (SUCCESS);
	}
	if (env->parsing_state == NORMAL || env->parsing_state == START ||
		env->parsing_state == END)
		parsing_room(env, line);
	return (SUCCESS);
}
