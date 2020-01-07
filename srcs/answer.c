# include "lem-in.h"

static int 		make_answer(t_env *env, size_t i, size_t k)
{
	t_answer	*answer;
	size_t	**matrice;
	size_t	*paths;
	size_t	j;
	t_path	*path;

	if (!(answer = create_answer(env)))
		return (FAILURE);
	matrice = env->answer_matrice;
	answer->nb_path = k + 1;
	if (!(paths = (size_t *)malloc(sizeof(size_t) * (k + 2))))
		return (FAILURE);
	paths[0] = i;
	j = 0;
	k = 0;
	while (j <= env->path_idmax)
	{
		if (matrice[i][j] == 1)
			paths[++k] = j;
		j++;
	}
	i = 0;
	while (i < answer->nb_path)
	{
		path = env->path;
		while (path->id != paths[i])
			path = path->next;
		answer->steps += path->steps;
		i++;
	}
	if (env->steps == 0 || answer->steps < env->steps)
	{
		env->steps = answer->steps;
		answer->best = 1;
	}
	answer->path = paths;
	i = 0;
	while (i < answer->nb_path)
	{
		printf("path id = %zu\n", paths[i]);
		i++;
	}
	printf("answer->steps = %zu || ", answer->steps);
	printf("answer->nb_path = %zu || ", answer->nb_path);
	printf("answer->best = %zu\n", answer->best);
	return (SUCCESS);
}

static int		explore_answer_matrice(t_env *env)
{
	size_t		**matrice;
	size_t		i;
	size_t		j;
	size_t		k;

	matrice = env->answer_matrice;
	i = 0;
	while (i <= env->path_idmax)
	{
		j = 0;
		k = 0;
		while (j <= env->path_idmax)
		{
			if (matrice[i][j] == 1)
				k++;
			j++;
		}
		if (k != 0)
		{
			if (make_answer(env, i, k) == FAILURE)
				return (FAILURE);
		}
		i++;
	}
	return(SUCCESS);
}

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
	printmatrice(env);
	printf("nb path max = %zu\n", env->nb_paths_used);
}

static	void 	set_resolution(t_env *env)
{
	t_path	*path;
	t_path	*tmp;
	t_answer *answer;

	path = env->path;
	while (path)
	{
		if (!tmp || path->steps < tmp->steps)
			tmp = path;
		path = path->next;
	}
	// printf("id path = %zu || steps = %zu\n", tmp->id, tmp->steps);
	answer = env->answer;
	while (answer)
	{
		if (answer->best == 1)
			break ;
		answer = answer->next;
	}
	if ((tmp->steps + env->ants) < (((answer->steps / answer->nb_path) + (answer->steps % answer->nb_path)) + (env->ants / answer->nb_path + env->ants % answer->nb_path)))
	{
		env->steps = (tmp->steps + env->ants);
		env->resolution = STRAIGHT;
	}
	else
	{
		env->steps = (((answer->steps / answer->nb_path) + (answer->steps % answer->nb_path)) + (env->ants / answer->nb_path + env->ants % answer->nb_path));
		env->resolution = MULTIPATH;
		env->answer = answer;
	}
	printf("straight = %zu\n", (tmp->steps + env->ants));
	printf("multipath = %zu\n", (((answer->steps / answer->nb_path) + (answer->steps % answer->nb_path)) + (env->ants / answer->nb_path + env->ants % answer->nb_path)));
 	printf("resolution = %zu\n", env->resolution);
}

int			find_turns(t_env *env)
{
	find_nb_path(env);
	put_id_path(env);
	set_answer_matrice(env);
	if (explore_answer_matrice(env) == FAILURE)
		return (FAILURE);
	set_resolution(env);
	return (SUCCESS);
}
