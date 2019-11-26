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

int   main(void)
{
    t_env *env;

    env = processinit();
    if (processparsing(env) == SUCCESS)
        printf("ants = %lu\n", env->ants);
	select_answer(env);
    tafreetatoucompri(env);
    return (0);
}
