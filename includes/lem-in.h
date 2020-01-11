/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemmin.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artprevo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 18:27:52 by artprevo          #+#    #+#             */
/*   Updated: 2019/11/22 16:58:11 by artprevo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMMIN_H
# define LEMMIN_H

# include "libft.h"

# define BUFFER_SIZE	10000
# define SHIFT_MIN		32
# define TRUE			1
# define FALSE 			0
# define SUCCESS 		0
# define FAILURE 		-1

# define ANTS			-1
# define NORMAL			0
# define START			1
# define END			2
# define PIPE			3

# define NAME			0
# define XROOM			1
# define YROOM			2

# define A				0
# define B				1

# define STRAIGHT		1
# define MULTIPATH		2

// # define X				0
// # define Y				1
// # define UP				1
// # define DOWN			-1
// # define RIGHT			1
// # define LEFT			-1

typedef	struct			s_env
{
	struct s_room 		*room;
	struct s_pipe		*pipe;
	struct s_path		*path;
	struct s_answer		*answer;
	struct s_ants		*ants_list;
	size_t				**matrice;
	size_t				**answer_matrice;
	size_t				idmax;
	size_t				path_idmax;
	size_t				steps;
	size_t				ants;
	int					parsing_state;
	size_t				resolution;
	size_t				nb_paths_used;
	size_t				turns;
}						t_env;

typedef struct			s_path
{
	struct s_ways		*ways;
	struct s_path		*next;
	size_t				id;
	size_t				steps;
	size_t				turns;
	size_t				usable;
}						t_path;

typedef struct			s_ways
{
	size_t				ants;
	size_t				id;
	struct s_ways		*next;
}						t_ways;

typedef	struct			s_room
{
	size_t				state;
	size_t				id;
	char				*name;
	struct s_room		*next;
	struct s_room 		*prev;
}						t_room;

typedef struct			s_pipe
{
	size_t				used;
	char				*a;
	char				*b;
	size_t				ida;
	size_t				idb;
	struct s_pipe		*next;
	struct s_pipe		*prev;
}						t_pipe;

typedef struct			s_answer
{
	size_t				*path;
	size_t				best;
	size_t				nb_path;
	size_t				steps;
	struct s_answer		*next;
}						t_answer;

typedef struct			s_ants
{
	size_t				arrived;
	size_t				id;
	t_path				*path;
	struct s_ants		*next;
}						t_ants;

// main.c
int						processparsing(t_env *env);

// parsing.c
int						checktype(t_env *env, char *line);

// init.c
t_pipe					*initpipe(void);
t_room					*initroom(void);
t_env					*processinit(void);
t_path					*initpath(void);
t_ways					*initways(size_t id);
t_answer				*initanswer(void);
t_ants					*initants(t_path *path, size_t id);

// init_tools.c
t_room					*create_room(t_env *env);
t_pipe					*create_pipe(t_env *env);
t_ways					*create_ways(t_path *path, size_t id);
t_path					*create_path(t_env *env);
t_answer				*create_answer(t_env *env);
t_ants					*create_ants(t_env *env, t_path *path, size_t id);

// setup_id.c
void					put_id_room(t_env *env, size_t id);
void 					put_id_path(t_env *env);


// matrice.c
int						set_matrice(t_env *env);
size_t					recursive(t_env *env, size_t **matrice, size_t i);
int						make_path(t_env *env);
int						fill_ways(t_env *env, t_path *path, size_t **matrice, size_t steps);
size_t					did_not_pass(t_env *env, size_t *line);

// matrice2.c
int						explore_matrice(t_env *env, size_t i, size_t j, size_t **matrice);

// answermatrice.c
int						set_answer_matrice(t_env *env);
t_path					*find_path(size_t i, t_env *env);

// freeall.c
void					tafreetatoucompri(t_env *env);

// utility.c
size_t					absolute(int i);
void 					reso_calcul(t_env *env, t_path *tmp, t_answer *answer);
size_t					*add_path(t_env *env, size_t **matrice,
						size_t k, size_t i);

// result.c
int						print_result(t_env *env, size_t id);
void					print_answer(t_env *env, size_t ants, size_t idroom);

// result2.c
t_ways					*mp_tool1(t_env *env, t_ways *ways, t_ants *ants, size_t space);
t_ways					*mp_tool2(t_env *env, t_ways *ways, t_ants *ants, size_t space);
t_ways					*mp_tool3(t_ants *ants);
void 					mp_tool4(t_env *env);
t_ants 					*mp_tool5(t_env *env, size_t *i, size_t *j);

// print.c
void 					printpipe(t_env *env);
void 					printroom(t_env *env);
void 					printmatrice(t_env *env);
void 					printpath(t_env *env);
void 					printmatrice2(t_env *env);

int						find_turns(t_env *env);

#endif
