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

static void big_clean(t_env *env, size_t **matrice, size_t i)
{
	size_t	j;

	j = 0;
	while (j <= env->path_idmax)
	{
		if (matrice[i][j] == 1)
			matrice[j][i] = 0;
		j++;
	}
}

static void	clean_answer(t_env *env, size_t i, size_t count, size_t k)
{
	size_t	j;
	size_t	**matrice;
	size_t	k_bis;

	matrice = env->answer_matrice;
	j = 0;
	k_bis = 0;
	// printf("matrice avant clean\n");
	// printmatrice2(env);
	// printf("count clean = %zu || k clean = %zu\n", count, k);
	while (j <= env->path_idmax)
	{
		if (matrice[i][j] == 2)
		{
				k_bis++;
				matrice[i][j] = 1;
				if (k_bis == k && k != 1)
					matrice[i][j] = 2;
		}
		j++;
	}
	// printf("matrice apres clean\n");
	// printmatrice2(env);

}

static size_t mini_scout(size_t **matrice, size_t i, size_t max)
{
	size_t	j;
	size_t	ret;

	j = 0;
	ret = 0;
	while (j <= max)
	{
		if (matrice[i][j] == 2)
			ret++;
		j++;
	}
	return (ret);
}

static int	algo_answer(t_env *env, size_t count, size_t i, size_t k)
{
	size_t	**matrice;
	size_t	j;
	size_t	count_bis;
	size_t	k_bis;

	// printf("k = %zu\n", k);
	matrice = env->answer_matrice;
	count_bis = 0;
	k_bis = mini_scout(matrice, i, env->path_idmax);
	j = 0;
	// printf("count_bis = %zu || j = %zu || k_bis = %zu\n", count_bis, j, k_bis);
	while (k_bis != k)
	{
		if (matrice[i][j] == 1)
		{
			count_bis++;
			if (count_bis >= count)
			{
				k_bis++;
				matrice[i][j] = 2;
			}
		}
		// count_bis++;
		j++;
		// printf("count_bis = %zu || j = %zu || k_bis = %zu\n", count_bis, j, k_bis);
	}
	if (make_answer(env, i, k) == FAILURE)
		return (FAILURE);
	// printf("answer !\n");
	clean_answer(env, i, count, k);
	return (SUCCESS);
}

int		algo_multipath(t_env *env, size_t i, size_t k)
{
	size_t	**matrice;
	size_t	k_bis;
	size_t	count;
	size_t	regulator;

	matrice = env->answer_matrice;
	// k = nombre de chemins compatibles avec le chemin etudie i;
	// on incremente k_bis jusqu'a k pour faire toutes les solutions;
	// count est cense nous permettre de decrementer les solutions evaluees;
	k_bis = 1;
	regulator = 0;
	while (k_bis <= k)
	{
		count = k - regulator;
		// int n = (int)(k );
		// int g = (int)k_bis;
		// int f_n = ft_recursive_factorial(n);
		// int f_g = ft_recursive_factorial(g);
		// int f_n_g = ft_recursive_factorial(n - g);
		// printf("%d parmi %d = %d\n", g, n, (f_n) / (f_g * f_n_g));
		// printf("k = %zu || k_bis = %zu || count = %zu\n", k, k_bis, count);
		// printf("on recommence\n");
		while (count != 0)
		{
			// printf("k = %zu || k_bis = %zu || count = %zu\n", k, k_bis, count);
			if (algo_answer(env, count - k_bis + 1 + regulator, i, k_bis) == FAILURE)
				return (FAILURE);
			count--;
			// clean_answer();
		}
		// printf("fin de boucle, count = 0\n");
		clean_answer(env, i, count, 1);
		regulator++;
		k_bis++;
	}
	// big_clean(env, matrice, i);
	// printf("big clean down\n");
	return (SUCCESS);
}
