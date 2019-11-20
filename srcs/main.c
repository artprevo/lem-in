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
    maketab(env);
    if (path(env) == FAILURE)
        return (FAILURE);
    return (SUCCESS);
}

int   main(void)
{
    t_env *env;

    env = processinit();
    if (processparsing(env) == SUCCESS)
        printf("ants = %lu\n", env->ants);
    tafreetatoucompri(env);
    return (0);
}
