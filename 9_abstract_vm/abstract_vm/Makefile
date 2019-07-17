# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tdeborde <tdeborde@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/16 16:42:31 by tdeborde          #+#    #+#              #
#    Updated: 2019/07/17 19:51:36 by tdeborde         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME  = avm

# Compiler #
CC    = clang++

# Flags #
FLAGS = -std=c++11 -Wall -Wextra -Werror

# Sources #
SRC_NAME	= 	Lexer/AVMInput.cpp \
				Lexer/Lexer.cpp \
				Lexer/Token.cpp \
				Exceptions/Exceptions.cpp \
				Instructions/InstructionPush.cpp \
				Instructions/InstructionExit.cpp \
				Instructions/InstructionFactory.cpp \
				Operands/OperandFactory.cpp \
				Operands/Operand.cpp \
				Parser/Parser.cpp \
				main.cpp


SRC = $(addprefix src/,$(SRC_NAME))

# Objects #
OBJ_NAME 	= $(SRC_NAME:.cpp=.o)
OBJ = $(addprefix src/,$(OBJ_NAME))

# Deps #
DEPS = -Isrc

# Rules #
.PHONY: all, clean, fclean, re
.SUFFIXES:

all:	$(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(LFLAGS) $(OBJ) -o $(NAME) -L.

$(OBJ): %.o : %.cpp
	$(CC) $(FLAGS) $(DEPS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all


.PHONY: all clean fclean re
