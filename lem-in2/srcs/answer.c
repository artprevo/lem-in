# include "lem-in.h"

// static void 	print_answer(size_t ants, char *str)
// {
// 	ft_putchar('L');
// 	ft_putnbr((int)ants);
// 	ft_putchar('-');
// 	ft_putstr(str);
// }

// static size_t	no_common_way(t_env *env, t_path *path, t_path *tmp)
// {
// 	t_ways	*ways;
// 	t_ways	*tmp_ways;
//
// 	ways = path->ways;
// 	while (ways)
// 	{
// 		while (ways->id == 0)
// 			ways = ways->next;
// 		tmp_ways = tmp->ways;
// 		while (tmp_ways->id == 0)
// 			tmp_ways = tmp_ways->next;
// 		if (ways->id == env->idmax)
// 			return (TRUE);
// 		while (tmp_ways)
// 		{
// 			if (tmp_ways->id == ways->id)
// 				return (FALSE);
// 			tmp_ways = tmp_ways->next;
// 		}
// 		ways = ways->next;
// 	}
// 	return (TRUE);
// }

static void 	find_nb_path(t_env *env)
{
	size_t	i;
	size_t	j;
	size_t	nb_paths_used;
	size_t	**matrice;

	matrice = env->matrice;
	nb_paths_used = 0;
	i = 0;
	j = 0;
	while (j <= env->idmax)
	{
		if (matrice[0][j] == 1)
			i++;
		j++;
	}
	j = 0;
	while (j <= env->idmax)
	{
		if (matrice[env->idmax][j] == 1)
			nb_paths_used++;
		j++;
	}
	env->nb_paths_used = (i <= nb_paths_used ? i : nb_paths_used);
}

int			find_turns(t_env *env)
{
	t_path	*path;
	t_path	*tmp;
	size_t	nb_paths_used;

	find_nb_path(env);
	path = env->path;
	while (path)
	{
		nb_paths_used = 0;
		tmp = env->path;
		while (tmp)
		{
			if (env->ants > tmp->steps && path->steps <= tmp->steps)
				nb_paths_used++;
			tmp = tmp->next;
		}
		if (nb_paths_used == env->nb_paths_used)
			printf("SOLUTION\nsteps = %zu\n", path->steps);
		path = path->next;
	}
	path = env->path;
	while (path)
	{
		if (path->usable == TRUE)
			printf("path->steps = %zu\n", path->steps);
		path = path->next;
	}
	return (SUCCESS);
}

// static int			find_turns2(t_env *env)
// {
// 	t_path	*path;
// 	t_path	*tmp;
// 	size_t	min_steps;
// 	size_t	same_steps;
//
// 	min_steps = 0;
// 	path = env->path;
// 	while (path)
// 	{
// 		same_steps = 1;
// 		min_steps = path->steps;
// 		tmp = env->path;
// 		while (tmp)
// 		{
// 			if (tmp->steps == min_steps && no_common_way(env, path, tmp) == TRUE)
// 				same_steps++;
// 			tmp = tmp->next;
// 		}
// 		// path->turns = (min_steps) + (env->ants / same_steps) - 1;
// 		if (env->turns == 0 || path->turns < env->turns)
// 			env->turns = path->turns;
// 		path = path->next;
// 	}
// 	return (SUCCESS);
// }
