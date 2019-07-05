# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cmaxime <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/23 12:28:31 by cmaxime           #+#    #+#              #
#    Updated: 2018/03/20 15:25:42 by cmaxime          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = main

all: $(NAME)

$(NAME):
	$(MAKE) -C ./libft
	$(MAKE) -C ./lem_in
	$(MAKE) -C ./dark_mole
	$(MAKE) -C ./esc_caper

clean:
	$(MAKE) clean -C ./libft
	$(MAKE) clean -C ./lem_in
	$(MAKE) clean -C ./dark_mole
	$(MAKE) clean -C ./esc_caper

fclean: clean
	$(MAKE) fclean -C ./libft
	$(MAKE) fclean -C ./lem_in
	$(MAKE) fclean -C ./dark_mole
	$(MAKE) fclean -C ./esc_caper

re: fclean all

.PHONY: all clean fclean re
