# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tdeborde <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/16 12:03:21 by tdeborde          #+#    #+#              #
#    Updated: 2018/03/05 16:42:53 by tdeborde         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ../push_swap
CC = gcc
FLAGS = -Wall -Wextra -Werror
LIB_DIR = ../libs
LIB_NEED = /Libft
DEBUG = no
ifeq ($(DEBUG), yes)
	FLAGS = -g -w
endif
LIBS = ../libs/libftprintf.a
INCLUDES = -I../includes
ROOT = ../srcs
SRCS =	push_swap.c \
	  	input_tools.c \
		input_tools2.c \
		input_tools3.c \
		input_tools4.c \
		ft_parser1.c \
		ft_parser2.c \
		get_next_line.c \
		ft_init_tabs.c \
		ft_instrucs1.c \
		ft_instrucs2.c \
		ft_instrucs3.c \
		list_tools.c \
		push_swap_tools1.c \
		push_swap_tools2.c \
		push_swap_tools3.c

OBJ = $(SRCS:%.c=%.o)

.PHONY: all clean fclean re

all : $(NAME)

%.o : %.c
	    $(CC) $(INCLUDES) -c $< -o $@ $(FLAGS)

%.o : $(ROOT)/%.c
	    $(CC) $(INCLUDES) -c $< -o $@ $(FLAGS)

$(NAME) : $(OBJ)
	    $(MAKE) "LIB_NEED = $(LIB_NEED)" -C $(LIB_DIR)
		$(CC) $(INCLUDES) $^ -o $@ $(LIBS)

clean :
	    $(MAKE) clean "LIB_NEED = $(LIB_NEED)" -C $(LIB_DIR)
		rm -f $(OBJ)

fclean :
	    $(MAKE) fclean "LIB_NEED = $(LIB_NEED)" -C $(LIB_DIR)
		rm -f $(OBJ) $(NAME)

re : fclean $(NAME)
