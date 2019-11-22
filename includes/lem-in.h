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
	struct s_tab		*tab;
	struct s_path		*path;
	size_t				nb_path;
	size_t				ants;
	int					parsing_state;
}						t_env;


typedef struct			s_tab
{
	char				**map;
	size_t				xmax;
	size_t				ymax;
}						t_tab;

typedef	struct			s_room
{
	size_t				x;
	size_t				y;
	size_t				state;
	size_t				used;
	char				*name;
	struct s_room		*next;
	struct s_room 		*prev;
}						t_room;

typedef struct			s_pipe
{
	size_t				used;
	char				*a;
	char				*b;
	struct s_pipe		*next;
	struct s_pipe		*prev;
}						t_pipe;

typedef struct			s_path
{
	char				**pathing;
	size_t				id;
	size_t				steps;
	size_t				ants;
	struct s_path		*next;
	struct s_path		*prev;
}						t_path;

// main.c
int						processparsing(t_env *env);

// parsing.c
int						checktype(t_env *env, char *line);

// init.c
t_path					*initpath(void);
t_pipe					*initpipe(void);
t_room					*initroom(void);
t_env					*processinit(void);

// init_tools.c
t_room					*create_room(t_env *env);
t_pipe					*create_pipe(t_env *env);
t_path					*create_path(t_env *env, size_t steps, char **pathing);

// tab.c
void 					maketab(t_env *env);

// freeall.c
void					tafreetatoucompri(t_env *env);

// utility.c
size_t					absolute(int i);

// pathing.c
// void       closest_path(t_pipe *pipe, size_t **pos, int i);

// pipe.c
// void            		connect_pipes(t_env *env);

// print.c
void 					printpipe(t_pipe *pipe);
void 					printroom(t_room *room);
void 					printmap(char **map);

// path.c
int						path(t_env *env);

#endif
