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

#include "lemin.h"

void        printroom(t_env *env)
{
	t_room *room;

	room = env->room;
	while (room)
	{
	    printf("name = %s || ", room->name);
		printf("id = %d || ", room->id);
	    printf("state = %d\n\n", room->state);
		room = room->next;
	}
}

void        printpipe(t_env *env)
{
	t_pipe	*pipe;

	pipe = env->pipe;
	while (pipe)
	{
		printf("ida = %d\n", pipe->ida);
		printf("idb = %d\n", pipe->idb);
		pipe = pipe->next;
	}
}

void 		printmatrice(t_env *env)
{
	int		i;
	int		j;
	int		**matrice;

	i = 0;
	matrice = env->matrice;
	printf("  ");
	while (i <= env->idmax)
	{
		printf("%d", i);
		i++;
	}
	i = 0;
	printf("\n");
	printf("\n");
	while (i <= env->idmax)
	{
		j = 0;
		printf("%d ", i);
		while (j <= env->idmax)
		{
			if (matrice[i][j] != 1 && matrice[i][j] != 2 && matrice[i][j] != 3)
				matrice[i][j] = 0;
			printf("%d", matrice[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

void 		printmatrice2(t_env *env)
{
	int		i;
	int		j;
	int		**matrice;

	i = 0;
	matrice = env->answer_matrice;
	printf("  ");
	while (i <= env->path_idmax)
	{
		printf("%d", i);
		i++;
	}
	i = 0;
	printf("\n");
	printf("\n");
	while (i <= env->path_idmax)
	{
		j = 0;
		printf("%d ", i);
		while (j <= env->path_idmax)
		{
			if (matrice[i][j] != 1 && matrice[i][j] != 2 && matrice[i][j] != 3)
				matrice[i][j] = 0;
			printf("%d", matrice[i][j]);
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
			printf("%d || ", ways->id);
			ways = ways->next;
		}
		printf("\nidbis = %d\n", path->idbis);
		printf("id = %d || steps = %d\n", path->id, path->steps);
		path = path->next;
	}
}

void 		printanswer(t_env *env)
{
	t_answer	*answer;
	int		i;
	int		score;

	answer = env->answer;
	while (answer)
	{
		i = 0;
		while (i < answer->nb_path)
			printf("path = %d ||", answer->path[i++]);
		// printf("\n");
		printf(" answer->steps = %d || answer->nb_path = %d\n", answer->steps, answer->nb_path);
		score = ((answer->steps / answer->nb_path) +
		(answer->steps % answer->nb_path) + (env->ants / answer->nb_path) +
		(env->ants % answer->nb_path));
		// printf("score = %d\n\n", score);
		answer = answer->next;
	}
}
