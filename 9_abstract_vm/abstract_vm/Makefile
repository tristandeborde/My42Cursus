# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tdeborde <tdeborde@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/16 16:42:31 by tdeborde          #+#    #+#              #
#    Updated: 2019/06/11 16:46:59 by tdeborde         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME  = avm

# Compiler #
CC    = clang++

# Flags #
FLAGS = -Wall -Wextra -Werror

# Sources #
SRC_NAME	= 	main.cpp \
				AVMInput.cpp \
				Lexer.cpp \
				Parser.cpp \
				Token.cpp \
				Instruction.cpp

SRC = $(addprefix src/,$(SRC_NAME))

# Objects #
OBJ_NAME 	= $(SRC_NAME:.cpp=.o)
OBJ = $(addprefix obj/,$(OBJ_NAME))

# Deps #
DEPS = -Iinclude

# Rules #
.PHONY: all, clean, fclean, re
.SUFFIXES:

all:	$(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(LFLAGS) $(OBJ) -o $(NAME) -L.

$(OBJ): obj/%.o : src/%.cpp
	$(CC) $(FLAGS) $(DEPS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all


.PHONY: all clean fclean re
