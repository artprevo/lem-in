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
	size_t				**matrice;
	size_t				idmax;
	size_t				ants;
	int					parsing_state;
	size_t				nb_paths_used;
	size_t				turns;
}						t_env;

typedef struct			s_path
{
	struct s_ways		*ways;
	struct s_path		*next;
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

// init_tools.c
t_room					*create_room(t_env *env);
t_pipe					*create_pipe(t_env *env);
t_ways					*create_ways(t_path *path, size_t id);
t_path					*create_path(t_env *env);

// setup_id.c
void					put_id_room(t_env *env);

// matrice.c
int						set_matrice(t_env *env);
// freeall.c
void					tafreetatoucompri(t_env *env);

// utility.c
size_t					absolute(int i);

// print.c
void 					printpipe(t_env *env);
void 					printroom(t_env *env);
void 					printmatrice(t_env *env);
void 					printpath(t_env *env);

int						find_turns(t_env *env);

#endif
