# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: artprevo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/18 18:16:55 by artprevo          #+#    #+#              #
#    Updated: 2019/10/29 15:44:13 by artprevo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in
CC = clang
CFLAGS = -Wall -Wextra -Werror
SRCS = main.c init.c init_tools.c parsing.c freeall.c utility.c print.c \
setup_id.c matrice.c answer.c answermatrice.c result.c init2.c init_tools2.c \
matrice2.c result2.c error.c parsing2.c

OBJS_PATH = objs/
SRCS_PATH = srcs/
OBJS = $(patsubst %.c, $(OBJS_PATH)%.o, $(SRCS))
LIBFT = libft/libft.a
HEADER = ./includes/lemin.h ./libft/libft.h
INCLUDES = -I ./includes/ -I ./libft/

all: $(LIBFT) $(OBJS_PATH) $(NAME)

$(NAME): $(OBJS)
	printf "\033[0;36m> Compiling lem-in\033[0m"
	$(CC) $(CFLAGS) $(INCLUDES) -Llibft/ -lft $^ -o $@
	printf "\033[0;32m OK\n\033[0m"

$(OBJS): $(OBJS_PATH)%.o: $(SRCS_PATH)%.c $(HEADER)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJS_PATH):
	mkdir $@

$(LIBFT): FORCE
	$(MAKE) -C libft/

FORCE:

clean:
	$(RM) -R $(OBJS_PATH)
	$(MAKE) -C libft/ clean

fclean: clean
	$(MAKE) -C libft/ fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean re all
.SILENT:
