#include "lemin.h"

static void	print_int_tab(int *tab, int len, char *str)
{
	int i = 0;

	if (str)
	printf("%s", str);
	while (i < len)
	{
		printf("%d", tab[i]);
		i++;
	}
	printf("\n");
}

// void	print_tab(int *tab, int size)
// {
// 	for (int i = 0; i < size; i++)
// 		printf("%d", tab[i]);
// 	printf("\n");
// }
//
static void	print_path_list(t_pth *pth)
{
	while (pth)
	{
		if (pth->size != 0)
		{
			printf("[%d]", pth->size);
			print_int_tab(pth->path, pth->size, " ");
		}
		pth = pth->next;
	}
}

static int		*create_range_tab(int	range)
{
	int *tab;
	int	i;

	i = -1;
	if (!(tab = malloc(sizeof(*tab) * range)))
		return (0);
	while (++i < range)
		tab[i] = i;
	return (tab);
}

static int		*create_path2(int *parent_path, int value, int depth)
{
	int		*res;
	int		i;

	i = 0;
	if (!(res = malloc(sizeof(int) * depth)))
		return (0);
	if (parent_path)
	{
		while (i < depth - 1)
		{
			res[i] = parent_path[i];
			i++;
		}
	}
	res[depth - 1] = value;
	return (res);
}

static t_pth		*add_pth(t_pth *pth, t_num *son, int size)
{
	t_pth	*new;

	if (!(new = malloc(sizeof(*new))))
		return (0);
	new->path = son->path;
	new->size = size;
	new->next = pth;
	new->ptr = son;
	return (new);
}

static t_pth		*create_sons(t_num *num, int range, int max_son, t_pth *pth)
{
	int id;

	id = -1;
	if (!(num->sons = malloc(sizeof(t_num *) * range)))
		return (0);
	while (++id < max_son)
	{
		if (!(num->sons[id] = malloc(sizeof(t_num))))
			return (0);
		if (num->sons[id] == 0)
			return(0);
		num->son_count += 1;
		num->sons[id]->son_count = 0;
		num->sons[id]->depth = num->depth + 1;
		num->sons[id]->value = num->value + id + 1;
		if (!(num->sons[id]->path = create_path2(num->path, num->sons[id]->value,
			num->sons[id]->depth - 1)))
			return (0);
		if (!(pth = add_pth(pth, num->sons[id], num->sons[id]->depth - 1)))
			return (0);
		num->sons[id]->sons = NULL;
		if (!(pth = create_sons(num->sons[id], range, max_son - 1 - id, pth)))
			return (0);
	}
	return (pth);
}

static void		free_pth_tree(t_pth *pth)
{
	t_pth	*tmp;

	while (pth)
	{
		tmp = pth->next;
		free(pth->path);
		free(pth->ptr->sons);
		free(pth->ptr);
		free(pth);

		pth = tmp;
	}
}

static t_pth		*create_possibility_tree(int *tab, int range, t_pth *pth)
{
	t_num	*num;

	range++;
	if (!(num = malloc(sizeof(*num))))
		return (0);
	num->value = -1;
	num->son_count = 0;
	num->depth = 1;
	num->path = 0;
	if (!(pth = create_sons(num, range, range - 1, pth)))
		return (0);
	free(num->sons);
	free(num);
	return (pth);
}

static void 		setup_idbis(t_env *env, size_t i)
{
	size_t		**matrice;
	t_path		*path;
	size_t		j;
	size_t		id;

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

static t_path				*find_path2(size_t i, t_env *env)
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

static void 		swap_id(t_env *env, t_pth *pth)
{
	t_path	*path;
	size_t	i;

	while (pth)
	{
		printf("slt\n");
		if (pth->size == 1)
			pth->size = 0;
		i = 0;
		while (i < pth->size)
		{
			path = find_path2(pth->path[i], env);
			pth->path[i] = path->id;
			i++;
		}
		pth = pth->next;
	}
}

int		store_paths(t_env *env, int range, size_t i)
{
	int		*tab;
	t_pth	*pth;

	pth = 0;
	if (!(tab = create_range_tab(range)))
		return (1);
	if (!(pth = create_possibility_tree(tab, range, pth)))
		return (2);
	free(tab);
	setup_idbis(env, i);
	swap_id(env, pth);
	env->pth = pth;
	print_path_list(pth);

	// a plus besoin list on free
	// free_pth_tree(pth);
	return (0);
}

// int		main(int argc, char **argv)
// {
// 	int		range = 10;
//
// 	if (store_paths(range) != 0)
// 		return (1);
// 	return (0);
// }
