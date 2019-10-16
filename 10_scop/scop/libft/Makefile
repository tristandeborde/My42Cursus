# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cmaxime <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/28 11:28:01 by cmaxime           #+#    #+#              #
#    Updated: 2019/01/29 14:22:09 by cmaxime          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

_RED=$(shell tput setaf 1 2> /dev/null || echo "")
_GREEN=$(shell tput setaf 2 2> /dev/null || echo "")
_YELLOW=$(shell tput setaf 3 2> /dev/null || echo "")
_BLUE=$(shell tput setaf 4 2> /dev/null || echo "")
_PURPLE=$(shell tput setaf 5 2> /dev/null || echo "")
_CYAN=$(shell tput setaf 6 2> /dev/null || echo "")
_WHITE=$(shell tput setaf 7 2> /dev/null || echo "")
_END=$(shell tput sgr0 2> /dev/null || echo "")

# Formating
NORMAL=\x1b[0m
BOLD=\x1b[40m\x1b[1m

include files.mk

OBJBASIC = $(BASIC:%.c=.obj/%.o)
OBJPRINTF = $(PRINTF:%.c=.obj/%.o)
OBJALGEBRE = $(ALGEBRE:%.c=.obj/%.o)

OBJS = $(OBJBASIC) $(OBJPRINTF) $(OBJALGEBRE)

DEPS = ./Makefile \
	   ./include/libft.h

INCLUDE = -I include
GCC = gcc
FLAG = -Wall -Wextra -Werror -Weverything


all: $(NAME)

$(NAME): .obj $(OBJS) $(DEPS)
	@ar rc $(NAME) $(OBJS)
	@echo "$(BOLD)[ $(NAME) ] compiled$(NORMAL)"

.obj:
	@mkdir .obj

.obj/%.o: basic/%.c
	@printf "\\t%sCC%s\\t" "$(_GREEN)" "$(_END)"
	@$(GCC) $(INCLUDE) -c $< -o $@ $(FLAG)
	@printf "%s\\n" "$<"

.obj/%.o: printf/%.c
	@printf "\\t%sCC%s\\t" "$(_GREEN)" "$(_END)"
	@$(GCC) $(INCLUDE) -c $< -o $@ $(FLAG)
	@printf "%s\\n" "$<"

.obj/%.o: algebre/%.c
	@printf "\\t%sCC%s\\t" "$(_GREEN)" "$(_END)"
	@$(GCC) $(INCLUDE) -c $< -o $@ $(FLAG)
	@printf "%s\\n" "$<"

clean:
	@rm -rf .obj
	@printf "%s clean\\n" "$(NAME)"

fclean: clean
	@rm -f $(NAME)
	@printf "%s fclean\\n" "$(NAME)"

re: fclean all

.PHONY: clean fclean all re target
