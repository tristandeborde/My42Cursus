# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cmaxime <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/23 11:51:02 by cmaxime           #+#    #+#              #
#    Updated: 2018/03/06 09:33:51 by cmaxime          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ../dark-mole
FLAG = -Wall -Werror -Wextra
INC = ./includes
FSC = ./srcs/
LIB = ./lib/

SRC	= dark_mole.c \
	dm_draw.c \
	dm_node.c \
	dm_tnl.c \
	dm_destroy.c \
	dm_output.c \
	dm_images_update.c \
	dm_images_maping.c \
	dm_key_core.c \
	dm_key1.c \
	dm_key2.c \
	dm_keymap1.c \
	dm_controller_fcts.c \
	dm_buttons.c \
	dm_buttons_destroy.c \
	dm_circle.c \
	dm_image_menu.c \
	dm_view_controller.c

OBJ = $(SRC:%.c=%.o)

DEP = ./Makefile \
	  $(INC)/libft.h \
		$(INC)/dark_mole.h \
	  $(INC)/struct_darkmole.h

MLX = -lm -lmlx -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME): $(OBJ) $(DEP)
	$(MAKE) -C ../libft
	gcc $(OBJ) -o $(NAME) -L$(LIB) -lft $(MLX) $(FLAG)
	@echo "./dark-mole compiled..."

%.o: $(FSC)%.c
	gcc -I$(INC) -c $< -o $@ $(FLAG)

clean:
	$(MAKE) clean -C ../libft
	rm -f $(OBJ)
	@echo "Objets removed in ./dark_mole/ ..."

fclean: clean
	$(MAKE) fclean -C ../libft
	rm -f $(NAME)
	@echo "./dark-mole removed..."

re: fclean all

.PHONY: re all clean fclean
