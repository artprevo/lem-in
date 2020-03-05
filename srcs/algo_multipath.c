/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_multipath.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artprevo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 14:40:24 by artprevo          #+#    #+#             */
/*   Updated: 2020/02/02 14:40:35 by artprevo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int	process_tab(t_env *env, size_t *tab, size_t line, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	k;

	
	return (SUCCESS);
}

int		algo_multipath(t_env *env, size_t i, size_t k)
{
	size_t	*matrice;
	size_t	j;
	size_t	*tab;
	size_t	len;

	matrice = env->answer_matrice[i];
	j = 0;
	if (!(tab = (size_t *)malloc(sizeof(size_t) * (k + 1))))
		return (FAILURE);
	printf("size of malloc = %zu\n", k + 1);
	len = 1;
	tab[0] = i;
	while (j <= env->path_idmax)
	{
		if (matrice[j] == 1)
			tab[len++] = j;
		j++;
	}
	i = 0;
	while (i < (k + 1))
	{
		printf("tab[i] = %zu || i = %zu\n", tab[i], i);
		i++;
	}
	process_tab(env, tab, i, k + 1);
	exit (1);
	return (SUCCESS);
}
