# include "lem-in.h"

static size_t		did_not_pass(t_env *env, size_t *line)
{
	size_t i;
	size_t k;

	i = 0;
	k = 0;
	while (i <= env->idmax)
	{
		if (line[i] == 2)
			k++;
		i++;
	}
	if (k > 0)
		return (FALSE);
	return (TRUE);
}

static int		fill_ways(t_env *env, t_path *path, size_t **matrice)
{
	size_t	i;
	size_t	j;

	if (!(create_ways(path, 0)))
		return (FAILURE);
	i = 0;
	while (i <= env->idmax)
	{
		j = 0;
		while (j <= env->idmax)
		{
			if (matrice[i][j] == 2)
			{
				if (!(create_ways(path, j)))
					return(FAILURE);
				i = j;
				j = -1;
				// matrice[i][j] = 1;
			}
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

static int 		make_path(t_env *env, size_t steps)
{
	t_path	*path;
	size_t	**matrice;

	if (!(path = create_path(env)))
		return (FAILURE);
	matrice = env->matrice;
	path->steps = steps;
	if (fill_ways(env, path, matrice) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

static size_t 		recursive(t_env *env, size_t **matrice, size_t i)
{
	size_t	k;

	k = 0;
	while (k <= env->idmax) //i est la ligne de la matrice sans solution et on va chercher grace a la colonne quelle est la derniere salle visitee
	{
		// printf("i = %zu || k = %zu || matrice[k][i] = %zu\n", i, k, matrice[k][i]);
		if (matrice[k][i] == 2)
		{
			printf("i = %zu || k = %zu || matrice[k][i] = %zu\n", i, k, matrice[k][i]);
			matrice[k][i] = 1;
			if (matrice[k][env->idmax] == 1)
				return (k);
			i = k;
		}
		k++;
	}
	return (i);
}

static int			explore_matrice(t_env *env)
{
	size_t	i;
	size_t	j;
	size_t	steps;
	size_t	**matrice;

	i = 0;
	j = 0;
	steps = 1;
	matrice = env->matrice;
	while (j <= env->idmax)
	{
		if (j == env->idmax && i == 0)
			return (SUCCESS);
		if (matrice[i][j] == 1 && (did_not_pass(env, matrice[j]) == TRUE))
		{
			matrice[i][j] = 2;
			steps++;
			if (j == env->idmax)
			{
				printmatrice(env);
				if (make_path(env, steps) == FAILURE)
					return (FAILURE);
				printf("path cree\n");
				i = recursive(env, matrice, env->idmax);
				j = i;
				i = recursive(env, matrice, i);
				steps -= 2;
			}
			else if (i != env->idmax)
			{
				i = j;
				j = -1;
			}
		}
		else if (j == env->idmax && i != env->idmax)
		{
			steps--;
			j = i;
			i = recursive(env, matrice, i);
			// printf("i = %zu\n", i);
		}
		j++;
		if (j >= env->idmax && i == 0)
			return (SUCCESS);
	}
	printmatrice(env);
	return (SUCCESS);
}

int			set_matrice(t_env *env)
{
	size_t	**matrice;
	size_t	i;
	t_pipe	*pipe;

	if (!(matrice = (size_t **)malloc(sizeof(size_t *) * (env->idmax + 2))))
		return (FAILURE);
	i = 0;
	while (i <= env->idmax + 1)
	{
		if (!(matrice[i] = (size_t *)malloc(sizeof(size_t) * (env->idmax + 1))))
			return (FAILURE);
		i++;
	}
	matrice[--i] = NULL;
	pipe = env->pipe;
	while (pipe)
	{
		matrice[pipe->ida][pipe->idb] = 1;
		matrice[pipe->idb][pipe->ida] = 1;
		pipe = pipe->next;
	}
	env->matrice = matrice;
	printmatrice(env);
	if (explore_matrice(env) == FAILURE)
		return (FAILURE);
	printmatrice(env);
	printpath(env);
	return (SUCCESS);
}
