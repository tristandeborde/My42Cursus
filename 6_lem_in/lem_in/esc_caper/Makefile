# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cmaxime <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/23 11:51:02 by cmaxime           #+#    #+#              #
#    Updated: 2018/03/20 12:48:23 by cmaxime          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ../esc-caper
FLAG = -Wall -Werror -Wextra
INC = ./includes
FSC = ./srcs/
LIB = ./lib/

SRC	= esc_caper.c \
	ec_cnf_destroy.c \
	ec_image_update.c \
	ec_drawline.c \
	ec_set_pos.c \
	ec_3d_to_2d.c \
	ec_parser.c \
	ec_parse_ant.c \
	ec_parse_link.c \
	ec_parse_node.c \
	ec_parse_core.c \
	ec_parse_cmd.c \
	ec_parse_utils.c \
	ec_node.c \
	ec_ping.c \
	ec_ping_controller.c \
	ec_sphere.c \
	ec_sphere_utils.c \
	ec_sphere_map.c \
	ec_tube.c \
	ec_tube_map.c \
	ec_rev_euler.c \
	ec_key_core.c \
	ec_key1.c \
	ec_key2.c \
	ec_view_controller.c

OBJ = $(SRC:%.c=%.o)

DEP = ./Makefile \
	  $(INC)/libft.h \
	  $(INC)/esc_caper.h \
		$(INC)/struct_escaper.h

MLX = -lm -lmlx -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME): $(OBJ) $(DEP)
	$(MAKE) -C ../libft
	gcc $(OBJ) -o $(NAME) -L$(LIB) -lft $(MLX) $(FLAG)
	@echo "./$(NAME) compiled..."

%.o: $(FSC)%.c
	gcc -I$(INC) -c $< -o $@ $(FLAG)

clean:
	$(MAKE) clean -C ../libft
	rm -f $(OBJ)
	@echo "Objets removed in ./esc_caper/ ..."

fclean: clean
	$(MAKE) fclean -C ../libft
	rm -f $(NAME)
	@echo "./$(NAME) removed..."

re: fclean all

.PHONY: re all clean fclean
