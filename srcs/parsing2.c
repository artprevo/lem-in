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

char		*get_pipe_a(char *line)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	while (line[i] != '-')
		i++;
	if (!(tmp = ft_strnew(i + 1)))
		return (NULL);
	while (line[j] != '-')
	{
		tmp[j] = line[j];
		j++;
	}
	tmp[j] = '\0';
	return (tmp);
}

char		*get_pipe_b(char *line)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	while (line[i++])
	{
		if (line[i] == '-')
			j = i;
	}
	if (!(tmp = ft_strnew(i - j + 1)))
		return (NULL);
	i = 0;
	while (line[j])
		tmp[i++] = line[++j];
	return (tmp);
}

static int	checkants(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (ft_isdigit(line[i]) == 0)
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

int			checktype2(t_env *env, char *line)
{
	if (env->parsing_state == ANTS)
	{
		if (ft_strchr(line, '#') != 0)
			return (SUCCESS);
		if (checkants(line) == FAILURE)
			return (FAILURE);
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
	return (TRUE);
}
