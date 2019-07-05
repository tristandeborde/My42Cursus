# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tdeborde <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/05 12:28:44 by tdeborde          #+#    #+#              #
#    Updated: 2018/02/25 17:28:26 by tdeborde         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ROOT = $(shell pwd)

PRGS = $(ROOT)/checker_dir/  \
       $(ROOT)/push_swap_dir

LIB_NEED = /Libft

DEBUG = no

.PHONY: all clean fclean re

all :
	@for dir in $(PRGS) ; \
        do \
	        $(MAKE) "DEBUG = $(DEBUG)" "LIB_NEED = $(LIB_NEED)" -C $$dir; \
        done
clean :
	@for dir in $(PRGS) ; \
        do \
            $(MAKE) $@ "LIB_NEED = $(LIB_NEED)" -C $$dir; \
        done
fclean :
	@for dir in $(PRGS) ; \
        do \
			$(MAKE) $@ "LIB_NEED = $(LIB_NEED)" -C $$dir; \
		done
re : fclean all
