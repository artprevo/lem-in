#include "lemin.h"

void 		swap_id(t_env *env, t_pth *pth)
{
	t_path	*path;
	int	i;

	while (pth)
	{
		if (pth->size == 1)
			pth->size = 0;
		i = 0;
		while (i < pth->size)
		{
			path = find_path2(pth->path[i], env);
			// printf("path[i] = %d || path->id = %d\n", path[i], path->id);
			pth->path[i] = path->id;
			i++;
		}
		pth = pth->next;
	}
}

t_path			*find_path2(int i, t_env *env)
{
	t_path	*path;

	path = env->path;
	while (path)
	{
		if (path->idbis == i)
			return (path);
		path = path->next;
	}
	return (path);
}

// OK
void 		setup_idbis(t_env *env, int i)
{
	int		**matrice;
	t_path		*path;
	int		j;
	int		id;

	matrice = env->answer_matrice;
	j = 0;
	id = 0;
	path = find_path(i, env);
	path->idbis = id;
	while (j <= env->path_idmax)
	{
		if (matrice[i][j] == 1)
		{
			path = find_path(j, env);
			path->idbis = ++id;
		}
		j++;
	}
}