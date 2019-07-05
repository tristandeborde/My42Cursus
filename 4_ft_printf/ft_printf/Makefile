# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tdeborde <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/07 17:20:09 by tdeborde          #+#    #+#              #
#    Updated: 2018/01/26 17:54:53 by tdeborde         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
FLAGS = -Wall -Wextra -Werror
SRC = ft_strlen.c ft_strdup.c ft_strcpy.c ft_strncpy.c ft_strcmp.c ft_strncmp.c \
	  ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
	  ft_toupper.c ft_tolower.c ft_atoi.c ft_strstr.c ft_strnstr.c \
	  ft_strcat.c ft_strncat.c ft_strlcat.c ft_strchr.c ft_strrchr.c \
	  ft_bzero.c ft_memalloc.c ft_memset.c ft_memcpy.c ft_memccpy.c \
	  ft_memchr.c ft_memmove.c ft_memcmp.c ft_memdel.c ft_strnew.c ft_striter.c \
	  ft_putchar.c ft_strmap.c ft_strequ.c ft_strnequ.c ft_strmapi.c ft_strsub.c \
	  ft_strtrim.c ft_strsplit.c ft_putchar.c ft_putstr.c ft_putchar_fd.c \
	  ft_putstr_fd.c ft_putnbr.c ft_putendl.c ft_putendl_fd.c ft_itoa.c \
	  ft_lstadd.c ft_lstdel.c ft_lstiter.c ft_lstdelone.c ft_lstmap.c \
	  ft_lstnew.c ft_strclr.c ft_strdel.c ft_striteri.c ft_strjoin.c \
	  ft_putnbr_fd.c ft_itoa_base.c ft_atoi_base.c ft_itoa_ubase.c \
	  ft_atoi_ubase.c ft_putnbr_long.c ft_isupper.c \
	  ft_toupper_str.c ft_putbytes.c ft_strndup.c ft_strnjoin.c \
	  ./srcs/ft_process_args4.c srcs/ft_check_inputs.c srcs/ft_printf.c \
	  ./srcs/ft_init_tabs.c srcs/ft_process_args.c srcs/ft_apply_options.c \
	  srcs/ft_process_args2.c srcs/ft_process_args3.c srcs/ft_handle_prefix.c \
	  srcs/ft_handle_unicode.c srcs/ft_tools.c srcs/ft_handle_padding.c \
	  srcs/ft_handle_prefix.c srcs/ft_handle_precision.c srcs/ft_find_padding.c \
	  srcs/ft_launch_conv1.c srcs/ft_launch_conv2.c srcs/ft_printf_tools.c
	  
OBJ = $(SRC:%.c=%.o)

all: $(NAME)

%.o:  %.c
	gcc $(FLAGS) -c $< -o $@

$(NAME): $(OBJ)
	ar rc $@ $^

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
