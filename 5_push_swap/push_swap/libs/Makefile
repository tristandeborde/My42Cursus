# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tdeborde <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/05 12:41:03 by tdeborde          #+#    #+#              #
#    Updated: 2018/03/05 16:37:05 by tdeborde         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ROOT = $(shell pwd)
LIB_NEED = /Libft
DEBUG = no
.PHONY: all clean fclean re
all :
	@for dir in $(LIB_NEED) ; \
		do \
			$(MAKE) "DEBUG = $(DEBUG)" -C $(ROOT)$$dir; \
		done
clean :
	@for dir in $(LIB_NEED) ; \
		do \
			$(MAKE) $@ -C $(ROOT)$$dir; \
		done
fclean :
	@for dir in $(LIB_NEED) ; \
		do \
			$(MAKE) $@ -C $(ROOT)$$dir; \
		done
re : fclean all
