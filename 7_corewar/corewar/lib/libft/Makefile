# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: blefeuvr <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/29 11:26:31 by blefeuvr          #+#    #+#              #
#    Updated: 2018/05/01 09:58:13 by blefeuvr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

# Compiler #
CC = gcc

# Include #
CPPFLAGS = -Iinclude

# Flags #
CFLAGS = -Werror -Wall -Wextra

# Sources #
SRC_NAME =\
	ft_isnum.c\
	ft_isspace.c\
	ft_atoi_base_max.c\
	ft_abs.c\
	ft_atoi.c\
	ft_itoa_base.c\
	ft_atoi_base.c\
	ft_bzero.c\
	ft_cinstr.c\
	ft_gnl.c\
	ft_isalnum.c\
	ft_isalpha.c\
	ft_isascii.c\
	ft_isdigit.c\
	ft_isprint.c\
	ft_itoa.c\
	ft_lstdelif.c\
	ft_lstadd.c\
	ft_lstaddend.c\
	ft_lstdel.c\
	ft_lstdelone.c\
	ft_lstiter.c\
	ft_lstlast.c\
	ft_lstmap.c\
	ft_lstnew.c\
	ft_lstpush.c \
	ft_lstpushb.c \
	ft_lstpushf.c \
	ft_lstsize.c\
	ft_lstsort.c\
	ft_max.c\
	ft_memextend.c\
	ft_memsub.c\
	ft_memalloc.c\
	ft_memjoin.c\
	ft_memccpy.c\
	ft_memchr.c\
	ft_memclen.c\
	ft_memcmp.c\
	ft_memcpy.c\
	ft_memcpy_x.c\
	ft_memdel.c\
	ft_memmove.c\
	ft_memrealloc.c\
	ft_memset.c\
	ft_min.c\
	ft_pow.c\
	ft_putbit.c\
	ft_putchar.c\
	ft_putchar_fd.c\
	ft_putcolor_24.c \
	ft_putcolor_8.c \
	ft_putcolor_hex24.c \
	ft_putcolor_hex8.c \
	ft_putendl.c\
	ft_putendl_fd.c\
	ft_putnbr.c\
	ft_putnbr_fd.c\
	ft_putstr.c\
	ft_putstr_fd.c\
	ft_sqrt.c\
	ft_sqrtup.c\
	ft_strcat.c\
	ft_strccount.c\
	ft_strccpy.c\
	ft_strchr.c\
	ft_strclen.c\
	ft_strclr.c\
	ft_strcmp.c\
	ft_strcpy.c\
	ft_strdel.c\
	ft_strdel_tab.c\
	ft_strdup.c\
	ft_strexplode.c\
	ft_strequ.c\
	ft_strext.c\
	ft_strextend.c\
	ft_strisdigit.c\
	ft_strisnumber.c\
	ft_striter.c\
	ft_striteri.c\
	ft_strjoin.c\
	ft_strlcat.c\
	ft_strlen.c\
	ft_strmap.c\
	ft_strmapi.c\
	ft_strncat.c\
	ft_strncmp.c\
	ft_strncpy.c\
	ft_strndup.c\
	ft_strnequ.c\
	ft_strnew.c\
	ft_strnstr.c\
	ft_strrchr.c\
	ft_strrepl.c\
	ft_strsanitalize.c\
	ft_strsplit.c\
	ft_strstr.c\
	ft_strsub.c\
	ft_strtrim.c\
	ft_tolower.c\
	ft_toupper.c\
	ft_ulstadd_head.c\
	ft_ulstadd_tail.c\
	ft_ulstdel.c\
	ft_ulstdelone.c\
	ft_ulstnew.c\
	ft_ulstset_head.c\
	ft_ulstset_tail.c\
	ft_ulstsize.c\
	ft_ulsttsize.c
SRC_NAME +=\
	ft_realloc.c\
	ft_printf.c\
	ft_realloc_mem.c\
	pf_arg_arg.c\
	pf_arg_chr.c\
	pf_arg_def.c\
	pf_arg_int.c\
	pf_arg_ptr.c\
	pf_arg_str.c\
	pf_arg_uint.c\
	pf_arg_uint2.c\
	pf_collapse_buff.c\
	pf_core_parse.c\
	pf_declarations.c\
	pf_exception_zero.c\
	pf_init_t_print.c\
	pf_ltoa.c\
	pf_op1.c\
	pf_op2.c\
	pf_precision.c\
	pf_size.c\
	pf_t_print_cleaning.c\
	pf_va_arg.c\
	pf_wchar_to_char.c

SRC = $(addprefix /,$(SRC_NAME))

# Objects #
OBJ_NAME = $(SRC_NAME:.c=.o)
OBJ_PATH = obj/
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))

VPATH = ./src/conv/:./src/printf/types/:./src/is/:./src/list/:./src/math/:\
	./src/mem/:./src/printf/:./src/put/:./src/str/:./src/gnl/:\
	./src/printf/specs/:./src/printf/utils/

# Dependencies #
DEPS = include/*.h Makefile

# Rules #
.PHONY: all, clean, fclean, re
.SUFFIXES:

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $@ $^
	ranlib $(NAME)

$(OBJ_PATH)%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all
