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

static int		fill_pipe(t_env *env, t_pipe *pipe, char *line)
{
	char	*tmp_a;
	char	*tmp_b;
	t_room	*room;

	if (!(tmp_a = get_pipe_a(line)))
		return (FAILURE);
	if (!(tmp_b = get_pipe_b(line)))
		return (FAILURE);
	room = env->room;
	while (room)
	{
		if (tmp_a && ft_strcmp(tmp_a, room->name) != 0)
		{
			pipe->ida = room->id;
			free(tmp_a);
			tmp_a = NULL;
		}
		else if (tmp_b && ft_strcmp(tmp_b, room->name) != 0)
		{
			pipe->idb = room->id;
			free(tmp_b);
			tmp_b = NULL;
		}
		if (!tmp_a && !tmp_b)
			return (SUCCESS);
		room = room->next;
	}
	return (FAILURE);
}

static int		fill_room(t_env *env, t_room *room, char *line)
{
	char	*tmp;
	int		i;
	int		k;

	k = 0;
	i = 0;
	while (line[i] != ' ')
		i++;
	if (!(tmp = ft_strnew(i + 1)))
		return (FAILURE);
	i = 0;
	while (line[i] != ' ')
		tmp[k++] = line[i++];
	tmp[k] = '\0';
	if (!(room->name = ft_strdup(tmp)))
	{
		free(tmp);
		return (FAILURE);
	}
	room->id = env->idmax++;
	free(tmp);
	return (SUCCESS);
}

static int		parsing_room(t_env *env, char *line)
{
	t_room		*room;

	if (!(room = create_room(env)))
		return (FAILURE);
	if (check_room(line) != 2)
		return (FAILURE);
	if (fill_room(env, room, line) == FAILURE)
		return (FAILURE);
	room->state = env->parsing_state;
	env->parsing_state = NORMAL;
	return (SUCCESS);
}

int				checktype(t_env *env, char *line)
{
	t_pipe	*pipe;

	if (checktype2(env, line) == SUCCESS)
		return (SUCCESS);
	else if (checktype2(env, line) == FAILURE)
		return (FAILURE);
	if (ft_strchr(line, '#') != FALSE)
		return (SUCCESS);
	if (checklinerror(line) == TRUE)
		return (FAILURE);
	if (ft_strchr(line, '-') != FALSE)
	{
		if (env->room_parsed == 0)
		{
			put_id_room(env);
			env->room_parsed = 1;
		}
		if (!(pipe = create_pipe(env)))
			return (FAILURE);
		if (fill_pipe(env, pipe, line) == FAILURE)
			return (FAILURE);
		return (SUCCESS);
	}
	if (env->parsing_state == NORMAL || env->parsing_state == START ||
		env->parsing_state == END)
	{
		if (parsing_room(env, line) == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}
