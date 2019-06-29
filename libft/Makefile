# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bghandou <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/06 12:39:45 by bghandou          #+#    #+#              #
#    Updated: 2019/06/21 19:02:28 by bghandou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

AR = ar rc

CFLAGS = -Wall -Wextra -Werror

SRC = ./ft_atoi.c \
	  ./ft_splitwhite.c \
	  ./ft_strrev.c \
	  ./ft_isascii.c \
	  ./ft_strcat.c \
	  ./ft_strdup.c \
	  ./ft_strncmp.c \
	  ./ft_strstr.c \
	  ./ft_isdigit.c \
	  ./ft_strchr.c \
	  ./ft_strlcat.c \
	  ./ft_strncpy.c \
	  ./ft_tolower.c \
	  ./ft_isalnum.c \
	  ./ft_isprint.c \
	  ./ft_strcmp.c \
	  ./ft_strlen.c \
	  ./ft_strnstr.c \
	  ./ft_toupper.c \
	  ./ft_isalpha.c \
	  ./ft_memalloc.c \
	  ./ft_strcpy.c \
	  ./ft_strncat.c \
	  ./ft_strrchr.c \
	  ./ft_bzero.c \
	  ./ft_memset.c \
	  ./ft_memcpy.c \
	  ./ft_memccpy.c \
	  ./ft_memmove.c \
	  ./ft_memchr.c \
	  ./ft_memcmp.c \
	  ./ft_memdel.c \
	  ./ft_putchar.c \
	  ./ft_putstr.c \
	  ./ft_putnbr.c \
	  ./ft_strmap.c \
	  ./ft_strmapi.c \
	  ./ft_itoa.c \
	  ./ft_strnew.c \
	  ./ft_strdel.c \
	  ./ft_strclr.c \
	  ./ft_striter.c \
	  ./ft_striteri.c \
	  ./ft_strequ.c \
	  ./ft_strnequ.c \
	  ./ft_strsub.c \
	  ./ft_strjoin.c \
	  ./ft_strtrim.c \
	  ./ft_strsplit.c \
	  ./ft_putchar_fd.c \
	  ./ft_putstr_fd.c \
	  ./ft_putnbr_fd.c \
	  ./ft_putendl_fd.c \
	  ./ft_putendl.c \
	  ./ft_lstnew.c \
	  ./ft_lstdelone.c \
	  ./ft_lstdel.c \
	  ./ft_lstadd.c \
	  ./ft_lstiter.c \
	  ./ft_lstmap.c \
	  ./ft_strlenchar.c \
	  ./ft_itoa_base.c \
	  ./ft_putnbr_base.c \
	  ./ft_printlist.c \
	  ./get_next_line.c

NAME = libft.a

OBJ = $(SRC:.c=.o)

all :$(NAME)

$(NAME) : $(OBJ)
	$(AR) $(NAME) $(OBJ)
	ranlib $(NAME)

%o.:%.c
	$(CC) $(CFLAGS) -o $< $@ -c $(SRC)

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : clean fclean all re 
