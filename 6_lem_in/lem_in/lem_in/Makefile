# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cmaxime <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/23 12:25:05 by cmaxime           #+#    #+#              #
#    Updated: 2018/03/20 12:50:40 by cmaxime          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ../lem-in

FLAG = -Wall -Werror -Wextra
INC = ./includes
FSC = ./srcs/
LIB = ./lib/


SRC = lem_in.c \
		lm_node.c \
		lm_data.c \
		lm_parse_core.c \
		lm_parse_ant.c \
		lm_parse_node.c \
		lm_parse_node2.c \
		lm_parse_link.c \
		lm_parse_utils.c \
		lm_check_data.c \
		lm_link_vals_fill.c \
		lm_find_one_path.c \
		lm_output.c

OBJ = $(SRC:%.c=%.o)

DEP = ./Makefile \
	  $(INC)/lem_in.h \
	  $(INC)/libft.h \
	  $(INC)/struct_lem_in.h

all: $(NAME)

$(NAME): $(OBJ) $(DEP)
	$(MAKE) -C ../libft
	gcc $(OBJ) -o $(NAME) -L$(LIB) -lft $(FLAG)
	@echo "./lem-in compiled..."

%.o: $(FSC)%.c
	gcc -I$(INC) -c $< -o $@ $(FLAG)


clean:
	$(MAKE) clean -C ../libft
	rm -f $(OBJ)
	@echo "Objects removed in lem_in/ ..."

fclean: clean
	$(MAKE) fclean -C ../libft
	rm -f $(NAME)
	@echo "./lem-in removed ..."


re: fclean all

.PHONY: re all clean fclean
