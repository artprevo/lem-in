/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artprevo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 16:51:51 by artprevo          #+#    #+#             */
/*   Updated: 2020/07/01 19:59:25 by artprevo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# include "libft.h"
# include "unistd.h"
# include <pthread.h>

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

uint64_t				g_timer;

typedef	struct			s_env
{
	struct s_room		*room;
	struct s_pipe		*pipe;
	struct s_path		*path;
	struct s_answer		*answer;
	struct s_ants		*ants_list;
	struct s_pth		*pth;
	int				**matrice;
	int				**answer_matrice;
	int				*result;
	int				result_size;
	int				score;
	int				idmax;
	int				path_idmax;
	int				steps;
	int				ants;
	int					parsing_state;
	int				resolution;
	int				nb_paths_used;
	int				room_parsed;
	int				turns;
	int				wrote;
}						t_env;

typedef struct			s_path
{
	struct s_ways		*ways;
	struct s_path		*next;
	int				id;
	int				idbis;
	int				steps;
	int				turns;
}						t_path;

typedef struct			s_ways
{
	int				ants;
	int				id;
	struct s_ways		*next;
}						t_ways;

typedef	struct			s_room
{
	int				state;
	int				id;
	char				*name;
	struct s_room		*next;
	struct s_room		*prev;
}						t_room;

typedef struct			s_pipe
{
	char				*a;
	char				*b;
	int				ida;
	int				idb;
	struct s_pipe		*next;
	struct s_pipe		*prev;
}						t_pipe;

typedef struct			s_answer
{
	int				*path;
	int				best;
	int				nb_path;
	int				steps;
	struct s_answer		*next;
}						t_answer;

typedef struct			s_num
{
	int					value;
	int					depth;
	int					son_count;
	int					*path;
	struct s_num		**sons;
}						t_num;

typedef struct			s_pth
{
	int					*path;
	int					size;
	t_num				*ptr;
	struct	s_pth		*next;
}						t_pth;

typedef struct			s_ants
{
	int				arrived;
	int				id;
	t_path				*path;
	struct s_ants		*next;
}						t_ants;

int						processparsing(t_env *env);
int						checklinerror(char *line);

int						checktype(t_env *env, char *line);

t_pipe					*initpipe(void);
t_room					*initroom(void);
t_env					*processinit(void);
t_path					*initpath(void);
t_ways					*initways(int id);
t_answer				*initanswer(void);
t_ants					*initants(t_path *path, int id);

t_room					*create_room(t_env *env);
t_pipe					*create_pipe(t_env *env);
t_ways					*create_ways(t_path *path, int id);
t_path					*create_path(t_env *env);
t_answer				*create_answer(t_env *env);
t_ants					*create_ants(t_env *env, t_path *path, int id);

void					put_id_room(t_env *env);
void					put_id_path(t_env *env);

int						set_matrice(t_env *env);
int					recursive(t_env *env, int **matrice, int i);
int						make_path(t_env *env);
int						fill_ways(t_env *env, t_path *path,
						int **matrice, int steps);
int					did_not_pass(t_env *env, int *line);

int						explore_matrice(t_env *env, int i,
						int j, int **matrice);

int						set_answer_matrice(t_env *env);
t_path					*find_path(int i, t_env *env);

void					tafreetatoucompri(t_env *env);
void					freepipe(t_env *env);
void					freeants(t_env *env);

int					absolute(int i);
void					reso_calcul(t_env *env, t_path *tmp, t_answer *answer);
int					*add_path(t_env *env, t_pth *tab);
t_path					*find_best_path(t_env *env);
int						everyone_not_arrived(t_env *env);

int						print_result(t_env *env, int id);
void					print_answer(t_env *env, int ants, int idroom);

t_ways					*mp_tool1(t_env *env, t_ways *ways,
						t_ants *ants, int space);
t_ways					*mp_tool2(t_env *env, t_ways *ways,
						t_ants *ants, int space);
t_ways					*mp_tool3(t_env *env, t_ants *ants);
void					mp_tool4(t_env *env);
t_ants					*mp_tool5(t_env *env, int *i, int *j);

int						checkerror(t_env *env);
int						checklinerror(char *line);
int						check_room(char *line);
int						check_room_authencity(t_env *env, char *name);

int						checktype2(t_env *env, char *line);
char					*get_pipe_a(char *line);
char					*get_pipe_b(char *line);

t_answer				*make_answer(t_env *env);
int						algo_multipath(t_env *env, int i, int k);

int						find_turns(t_env *env);
void					okazou(t_env *env);
t_answer				*find_best_answer(t_env *env);

int						store_paths(t_env *env, int range, int i);

void 					setup_idbis(t_env *env, int i);
t_path					*find_path2(int i, t_env *env);
void 					swap_id(t_env *env, t_pth *pth);

#endif
