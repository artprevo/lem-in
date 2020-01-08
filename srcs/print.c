/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artprevo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 14:30:41 by artprevo          #+#    #+#             */
/*   Updated: 2020/01/07 14:30:42 by artprevo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

void        printroom(t_env *env)
{
	t_room *room;

	room = env->room;
	while (room)
	{
	    printf("name = %s || ", room->name);
		printf("id = %zu || ", room->id);
	    printf("state = %zu\n\n", room->state);
		room = room->next;
	}
}

void        printpipe(t_env *env)
{
	t_pipe	*pipe;

	pipe = env->pipe;
	while (pipe)
	{
	    printf("a = %s || ", pipe->a);
		printf("ida = %zu\n", pipe->ida);
	    printf("b = %s || ", pipe->b);
		printf("idb = %zu\n", pipe->idb);
		pipe = pipe->next;
	}
}

void 		printmatrice(t_env *env)
{
	size_t		i;
	size_t		j;
	size_t		**matrice;

	i = 0;
	matrice = env->matrice;
	printf("  ");
	while (i <= env->idmax)
	{
		printf("%zu", i);
		i++;
	}
	i = 0;
	printf("\n");
	printf("\n");
	while (i <= env->idmax)
	{
		j = 0;
		printf("%zu ", i);
		while (j <= env->idmax)
		{
			if (matrice[i][j] != 1 && matrice[i][j] != 2 && matrice[i][j] != 3)
				matrice[i][j] = 0;
			printf("%zu", matrice[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

void 		printmatrice2(t_env *env)
{
	size_t		i;
	size_t		j;
	size_t		**matrice;

	i = 0;
	matrice = env->answer_matrice;
	printf("  ");
	while (i <= env->path_idmax)
	{
		printf("%zu", i);
		i++;
	}
	i = 0;
	printf("\n");
	printf("\n");
	while (i <= env->path_idmax)
	{
		j = 0;
		printf("%zu ", i);
		while (j <= env->path_idmax)
		{
			if (matrice[i][j] != 1 && matrice[i][j] != 2 && matrice[i][j] != 3)
				matrice[i][j] = 0;
			printf("%zu", matrice[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}


void 		printpath(t_env *env)
{
	t_path	*path;
	t_ways	*ways;

	path = env->path;
	while (path)
	{
		ways = path->ways;
		while (ways)
		{
			printf("%zu || ", ways->id);
			ways = ways->next;
		}
		printf("steps = %zu\n", path->steps);
		path = path->next;
	}
}
