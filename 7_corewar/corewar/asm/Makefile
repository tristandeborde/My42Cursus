# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: blefeuvr <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/29 11:26:31 by blefeuvr          #+#    #+#              #
#    Updated: 2018/05/17 11:31:19 by cmaxime          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = asm

# Compiler #
CC = gcc

# Libs #
LIB_DIR = ../lib
LFLAGS = -L$(LIB_DIR)/libft -lft

# Include #
CPPFLAGS = -Iinclude -I$(LIB_DIR)/libft/include

# Flags #
CFLAGS = -Werror -Wall -Wextra -g3
DEBUG = no
ifeq ($(DEBUG), yes)
	CFLAGS = -g -w
endif

# Sources #
SRC_NAME = main.c \
		   cw_write.c \
		   cw_write_out.c \
		   ft_cleaner.c \
		   cw_parse_value.c \
		   cw_label_init.c \
		   cw_prog_init.c \
		   cw_err.c \
		   cw_display.c \
		   cw_global.c \
		   cw_parse.c \
		   cw_parse_comment.c \
		   cw_parse_header.c \
		   cw_parse_inst.c \
		   cw_parse_label.c \
		   cw_parse_param.c \
		   cw_parse_param_dir.c \
		   cw_parse_param_ind.c \
		   cw_parse_param_lab.c \
		   cw_parse_param_reg.c \
		   cw_parse_update_pc.c

SRC = $(addprefix /,$(SRC_NAME))

# Objects #
OBJ_PATH = obj/
OBJ_NAME = $(SRC_NAME:.c=.o)
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))

VPATH = ./src/:./src/parser/:./src/error/:

# Deps #
DEPS = include/*.h Makefile 
DEPS += $(shell find $(LIB_DIR) -type f -regex ".*\.[ch]")

# Rules #
.PHONY: all, clean, fclean, re
.SUFFIXES:

all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) -C $(LIB_DIR)/libft
	$(CC) $(LFLAGS) $(CFLAGS) $(OBJ) -o $@

$(OBJ_PATH)%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

clean:
	$(RM) $(OBJ)
	$(MAKE) clean -C $(LIB_DIR)/libft

fclean: clean
	$(RM) $(NAME)
	$(MAKE) fclean -C $(LIB_DIR)/libft

re:
	$(MAKE) fclean
	$(MAKE) all
