# include "lem-in.h"

static void 	print_answer(size_t ants, char *str)
{
	ft_putchar('L');
	ft_putnbr((int)ants);
	ft_putchar('-');
	ft_putstr(str);
}

static void		use_ways(t_env *env, t_path *path, size_t id, size_t ants)
{
	t_ways *ways;
	t_room *room;

	ways = path->ways;
	while (ways->id != id)
		ways = ways->next;
	ways->ants = ants;
	room = env->room;
	while (ways->id != room->id)
		room = room->next;
	print_answer(ants, room->name);
}

static void		use_path(t_env *env, t_path *path)
{
	t_ways	*ways;
	t_ways	*tmp;
	size_t	ants;
	size_t	passage;
	size_t	turn;

	ants = 1;
	turn = 1;
	printf("turn <= %zu\n", (path->steps + env->ants - 1));
	while (turn <= (path->steps + env->ants - 1))
	{
		ants = 1;
		while (ants <= env->ants)
		{
			passage = 0;
			while (passage <= turn)
			{
				ways = path->ways;
				while (ways)
				{
					if (ways->ants == 0)
						use_ways(env, path, ways->id, ants);
					ways = ways->next;
					ft_putchar('\n');
				}
				tmp = path->ways;
				if (turn > 1)
				{
					while (tmp && tmp->ants != ants)
						tmp = tmp->next;
					tmp->ants = 0;
				}
				passage++;
			}
			ants++;
		}
		turn++;
	}
}

int			select_answer(t_env *env)
{
	size_t	ants;
	t_path	*path;

	path = env->path;
	ants = env->ants;
	while (path)
	{
		if (path->steps <= ants)
			path->usable = TRUE;
		path = path->next;
	}
	path = env->path;
	while (path)
	{
		if (path->usable == TRUE)
		{
			use_path(env, path);
			return (SUCCESS);
		}
		path = path->next;
	}
	return (SUCCESS);
}
