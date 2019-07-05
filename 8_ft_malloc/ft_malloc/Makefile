# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tdeborde <tdeborde@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/16 16:42:31 by tdeborde          #+#    #+#              #
#    Updated: 2019/06/13 14:24:41 by tdeborde         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME  = libft_malloc_$(HOSTTYPE).so

# Compiler #
CC    = gcc

# Flags #
FLAGS = -Wall -Wextra -Werror
LFLAGS = -shared -lpthread

# Sources #
SRC_NAME	= 	malloc.c \
				print1.c \
				print2.c \
				engine1.c \
				engine2.c
SRC = $(addprefix src/,$(SRC_NAME))

# Objects #
OBJ_NAME 	= $(SRC_NAME:.c=.o)
OBJ = $(addprefix obj/,$(OBJ_NAME))

# Deps #
DEPS = -Iinclude

# Rules #
.PHONY: all, clean, fclean, re
.SUFFIXES:

all:	$(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(LFLAGS) $(OBJ) -o $(NAME) -L.
	@ln -sf $(NAME) libft_malloc.so

$(OBJ): obj/%.o : src/%.c
	$(CC) $(FLAGS) $(DEPS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME) libft_malloc.so

re:
	$(MAKE) fclean
	$(MAKE) all


.PHONY: all clean fclean re
