#include "lem-in.h"

int					processparsing(t_env *env)
{
	char	*line;

    line = NULL;
	while (get_next_line(0, &line) == TRUE)
    {
        if (checktype(env, line) == FAILURE)
            return (FAILURE);
	    free(line);
    }
	put_id_room(env);
	if (set_matrice(env) == FAILURE)
		return (FAILURE);
    return (SUCCESS);
}

static int			processtreatment(t_env *env)
{
	if (find_turns(env) == FAILURE)
		return (FAILURE);
	if (print_result(env) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int					main(void)
{
    t_env *env;

    env = processinit();
    if (processparsing(env) == FAILURE|| processtreatment(env) == FAILURE)
		printf("Erorr\n");
    tafreetatoucompri(env);
    return (0);
}
