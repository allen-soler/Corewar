# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nalonso <nalonso@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/31 16:42:00 by jallen            #+#    #+#              #
#    Updated: 2019/06/29 15:39:41 by jallen           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ccred="\033[0;31m"
ccyellow="\033[0;33m"
ccend="\033[0m"
ccgreen= "\033[0;32m"

# compiler

CC = gcc

# compilation flags

FLAGS = -Wall  -g

# program name

NAME = asm

# library including ft_printf and libft

LIBFT = libft

# folders

DIR_S = src

DIR_O = temporary

DIR_H = includes

# source files for the project

SOURCES =	check_args.c		\
			free_systems.c		\
			instruct_tokens.c	\
			para_list.c			\
			token_automata.c	\
			check_comma.c		\
			handle_errors.c		\
			search_point.c		\
			create_file.c		\
			handle_labels.c		\
			null_state.c		\
			main.c

# header files

HEADER_FILES = includes/asm.h \

# prefixing

SRCS = $(addprefix $(DIR_S)/,$(SOURCES))

OBJS = $(addprefix $(DIR_O)/,$(SOURCES:.c=.o))

# compile project

all: $(NAME)

$(NAME): $(OBJS) lib
	@gcc -o $(NAME) $(FLAGS) -I $(DIR_H) $(OBJS) $(LIBFT)/libft.a
	@echo "asm compiled"

$(DIR_O)/%.o: $(DIR_S)/%.c $(HEADER_FILES)
	@printf $(ccgreen)"compiled\t"$(ccend)
	@printf "$<\n"
	@mkdir -p temporary
	@$(CC) $(FLAGS) -I $(DIR_H) -o $@ -c $<


lib:
	@echo "Compiling libraries:"
	@printf $(ccyellow)"%-20s"$(ccred) $(LIBFT)
	@make -C $(LIBFT)

clean:
	@rm -f $(OBJS)
	@printf $(ccred)"temporary/*.o && temporary/\n"$(ccend)
	@rm -rf $(DIR_O)
	@printf $(ccred)"%s\n"$(ccend) $(LIBFT)
	@make clean -C $(LIBFT)

fclean: clean
	@rm -rf $(NAME) $(NAME).dSYM
	@printf $(ccred)"%s\n"$(ccend) $(NAME)
	@make fclean -C $(LIBFT)
	@printf $(ccred)"%s.a\n"$(ccend) $(LIBFT)

re: fclean all

.PHONY: clean fclean all re
