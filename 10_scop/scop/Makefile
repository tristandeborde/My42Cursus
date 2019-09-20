# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tdeborde <tdeborde@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/16 16:42:31 by tdeborde          #+#    #+#              #
#    Updated: 2019/09/20 11:49:16 by tdeborde         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME  = scop

# Compiler #
CC    = gcc

# Flags #
FLAGS = -g -Wall -Wextra -Werror

# Sources #
SRC_NAME	= 	test.c \
				glad.c


SRC = $(addprefix src/,$(SRC_NAME))

# Objects #
OBJ_NAME 	= $(SRC_NAME:.c=.o)
OBJ = $(addprefix src/,$(OBJ_NAME))

# Deps #
DEPS = -I/Users/tdeborde/.brew/Cellar/glfw/3.3/include -Iinclude -I/Users/tdeborde/.brew/Cellar/cglm/0.6.0/include
LIBS = -L/Users/tdeborde/.brew/Cellar/glfw/3.3/lib -L/Users/tdeborde/.brew/Cellar/cglm/0.6.0/lib -lglfw

# Rules #
.PHONY: all, clean, fclean, re
.SUFFIXES:

all:	$(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(LFLAGS) $(OBJ) -o $(NAME) $(LIBS)

$(OBJ): %.o : %.c
	$(CC) $(FLAGS) $(DEPS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all


.PHONY: all clean fclean re
