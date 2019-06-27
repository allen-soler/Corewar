# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bghandou <bghandou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/24 19:25:12 by bghandou          #+#    #+#              #
#    Updated: 2019/06/27 17:46:28 by bghandou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

INCLUDE = includes

CFLAGS = -g3 -fsanitize=address -Wall -Wextra -Werror -I $(INCLUDE)

SRC = srcs/null_state.c \
	  srcs/token_automata.c \
	  srcs/search_point.c \
	  srcs/para_list.c \
	  srcs/instruct_tokens.c \
	  srcs/free_systems.c \
	  srcs/check_args.c \
	  srcs/handle_errors.c \
	  srcs/check_comma.c \
	  srcs/handle_labels.c \
	  srcs/syntax/syntax_checker.c \

NAME = asm

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	@make -C libft/
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -L libft/ -lft

clean :
	make -C libft/ clean
	rm -f $(OBJ)

fclean : clean
	make -C libft/ fclean
	rm -f $(NAME)

re : fclean all

.PHONY : clean fclean all re
