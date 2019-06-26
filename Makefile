ccred="\033[0;31m"
ccyellow="\033[0;33m"
ccend="\033[0m"
ccgreen= "\033[0;32m"

# compiler

CC = gcc

# compilation flags

FLAGS = -Wall -g # -Wextra # -Werror 

# program name

NAME = corewar

# library including ft_printf and libft

LIBFT = libft

# folders

DIR_S = src

DIR_O = obj

DIR_H = includes

# source files for the project

SOURCES =	main.c			\
			t_env.c			\
			t_process.c		\
			parsing_args.c	\
			utils.c			\
			debbuging.c		\
			read_files.c	\
			loop.c			\
			op.c			\
			op_functions.c	\
			args_utils.c	\
			exit_vm.c

# header files

HEADER = vm.h

# prefixing

SRCS = $(addprefix $(DIR_S)/,$(SOURCES))

OBJS = $(addprefix $(DIR_O)/,$(SOURCES:.c=.o))

# compile project

all: $(NAME)

$(NAME): $(DIR_H) $(OBJS) lib
	@gcc -o $(NAME) $(FLAGS) -I $(DIR_H) $(OBJS) $(LIBFT)/libft.a
	@echo "corewar compiled"

$(DIR_O)/%.o: $(DIR_S)/%.c
	@printf $(ccgreen)"compiled\t"$(ccend)
	@printf "$<\n"
	@mkdir -p $(DIR_O)
	@$(CC) $(FLAGS) -I $(DIR_H) -o $@ -c $<

lib:
	@echo "Compiling libraries:"
	@printf $(ccyellow)"%-20s"$(ccred) $(LIBFT)
	@make -C $(LIBFT)

clean:
	@rm -f $(OBJS)
	@printf $(ccred)"$(DIR_O)/*.o && $(DIR_O)/\n"$(ccend)
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
