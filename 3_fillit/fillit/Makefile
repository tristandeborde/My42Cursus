# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pprikazs <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/16 12:03:21 by pprikazs          #+#    #+#              #
#    Updated: 2017/11/30 14:51:09 by pprikazs         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fillit
CC = gcc

DEBUG = no
FLAGS = -Wall -Wextra -Werror
ifeq ($(DEBUG), yes)
	FLAGS = -g
endif

INCLUDES = ./
LIB = -L./libft/
SRCS = ./main.c \
	   ./ft_backtracking.c \
	   ./ft_check_input.c \
	   ./ft_display_map.c \
	   ./ft_parser_tetri.c

OBJ = $(SRCS:./%.c=./%.o) 

.PHONY: all clean fclean re

$(NAME) : $(OBJ)
	$(MAKE) -C ./libft/
	$(CC) $(LIB) $^ -o $@ -lft

all : $(NAME)

%.o : %.c
	$(CC) -I$(INCLUDES) -c $< -o $@ $(FLAGS)

clean :
	$(MAKE) clean -C ./libft/
	rm -f $(OBJ)

fclean : clean
	rm -f ./libft/libft.a
	rm -f $(NAME)

re : fclean $(NAME)
