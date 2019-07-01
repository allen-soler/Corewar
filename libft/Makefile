ccred="\033[0;31m"
ccyellow="\033[0;33m"
ccend="\033[0m"
ccgreen= "\033[0;32m"

CC = gcc
CFLAGS += -Wall -Werror -Wextra

NAME = libft.a

SRC_DIR 	= src/
DATA_STRUCTS	= data_structures/
IO			= io/
PRINTF		= printf/srcs/
TOOLS 		= tools/
LIBFT 		= libft/

HEADERS 	= ./includes

SRC += 	$(SRC_DIR)$(LIBFT)ft_memset.c		\
		$(SRC_DIR)$(LIBFT)ft_bzero.c		\
		$(SRC_DIR)$(LIBFT)t_garbage.c		\
		$(SRC_DIR)$(LIBFT)ft_splitwhite.c	\
		$(SRC_DIR)$(LIBFT)ft_memcpy.c		\
		$(SRC_DIR)$(LIBFT)ft_memccpy.c		\
		$(SRC_DIR)$(LIBFT)ft_memmove.c		\
		$(SRC_DIR)$(LIBFT)ft_memchr.c		\
		$(SRC_DIR)$(LIBFT)ft_memcmp.c		\
		$(SRC_DIR)$(LIBFT)ft_strlen.c		\
		$(SRC_DIR)$(LIBFT)ft_strdup.c		\
		$(SRC_DIR)$(LIBFT)ft_strcpy.c		\
		$(SRC_DIR)$(LIBFT)ft_strncpy.c		\
		$(SRC_DIR)$(LIBFT)ft_strcat.c		\
		$(SRC_DIR)$(LIBFT)ft_split.c		\
		$(SRC_DIR)$(LIBFT)ft_strncat.c		\
		$(SRC_DIR)$(LIBFT)ft_strlcat.c		\
		$(SRC_DIR)$(LIBFT)ft_strchr.c		\
		$(SRC_DIR)$(LIBFT)ft_strrchr.c		\
		$(SRC_DIR)$(LIBFT)ft_strstr.c		\
		$(SRC_DIR)$(LIBFT)ft_strnstr.c		\
		$(SRC_DIR)$(LIBFT)ft_strcmp.c		\
		$(SRC_DIR)$(LIBFT)ft_strncmp.c		\
		$(SRC_DIR)$(LIBFT)ft_atoi.c			\
		$(SRC_DIR)$(LIBFT)ft_isalpha.c		\
		$(SRC_DIR)$(LIBFT)ft_isdigit.c		\
		$(SRC_DIR)$(LIBFT)ft_isalnum.c		\
		$(SRC_DIR)$(LIBFT)ft_isascii.c		\
		$(SRC_DIR)$(LIBFT)ft_isprint.c		\
		$(SRC_DIR)$(LIBFT)ft_toupper.c		\
		$(SRC_DIR)$(LIBFT)ft_tolower.c		\
		$(SRC_DIR)$(LIBFT)ft_isspace.c		\
		$(SRC_DIR)$(LIBFT)ft_isblank.c		\
		$(SRC_DIR)$(LIBFT)ft_isquote.c		\
		$(SRC_DIR)$(LIBFT)ft_max.c			\
		$(SRC_DIR)$(LIBFT)ft_realloc_tab.c 	\
		$(SRC_DIR)$(LIBFT)ft_memalloc.c		\
		$(SRC_DIR)$(LIBFT)ft_memdel.c		\
		$(SRC_DIR)$(LIBFT)ft_strnew.c		\
		$(SRC_DIR)$(LIBFT)ft_strdel.c		\
		$(SRC_DIR)$(LIBFT)ft_striter.c		\
		$(SRC_DIR)$(LIBFT)ft_striteri.c		\
		$(SRC_DIR)$(LIBFT)ft_strmap.c		\
		$(SRC_DIR)$(LIBFT)ft_strmapi.c		\
		$(SRC_DIR)$(LIBFT)ft_strequ.c		\
		$(SRC_DIR)$(LIBFT)ft_strnequ.c		\
		$(SRC_DIR)$(LIBFT)ft_strsub.c		\
		$(SRC_DIR)$(LIBFT)ft_strjoin.c		\
		$(SRC_DIR)$(LIBFT)ft_strtrim.c		\
		$(SRC_DIR)$(LIBFT)ft_strsplit.c		\
		$(SRC_DIR)$(LIBFT)ft_itoa.c			\
		$(SRC_DIR)$(LIBFT)ft_strclr.c		\
		$(SRC_DIR)$(LIBFT)ft_putchar.c		\
		$(SRC_DIR)$(LIBFT)ft_putchar_fd.c	\
		$(SRC_DIR)$(LIBFT)ft_putstr.c		\
		$(SRC_DIR)$(LIBFT)ft_putstr_fd.c	\
		$(SRC_DIR)$(LIBFT)ft_putnbr.c		\
		$(SRC_DIR)$(LIBFT)ft_putnbr_fd.c	\
		$(SRC_DIR)$(LIBFT)ft_putendl.c		\
		$(SRC_DIR)$(LIBFT)ft_putendl_fd.c	\
		$(SRC_DIR)$(LIBFT)ft_strver.c 		\
		$(SRC_DIR)$(LIBFT)ft_lstnew.c		\
		$(SRC_DIR)$(LIBFT)ft_lstdelone.c	\
		$(SRC_DIR)$(LIBFT)ft_lstdel.c		\
		$(SRC_DIR)$(LIBFT)ft_endswith.c		\
		$(SRC_DIR)$(LIBFT)ft_lstadd.c		\
		$(SRC_DIR)$(LIBFT)ft_lstiter.c		\
		$(SRC_DIR)$(LIBFT)ft_lstmap.c		\
		$(SRC_DIR)$(LIBFT)ft_strndup.c		\
		$(SRC_DIR)$(LIBFT)ft_strrnstr.c		\
		$(SRC_DIR)$(LIBFT)ft_tab_len.c		\
		$(SRC_DIR)$(LIBFT)ft_print_tab.c	\
		$(SRC_DIR)$(LIBFT)ft_free_tab.c		\
		$(SRC_DIR)$(LIBFT)ft_realloc.c 		\
		$(SRC_DIR)$(IO)ft_read_stdin.c 		\
		$(SRC_DIR)$(IO)gnl_stdout.c 		\
		$(SRC_DIR)$(IO)get_next_line.c 		\
		$(SRC_DIR)$(IO)read_file.c 			\
		$(SRC_DIR)$(DATA_STRUCTS)avl/avl.c 					\
		$(SRC_DIR)$(DATA_STRUCTS)avl/avl_insert.c 			\
		$(SRC_DIR)$(DATA_STRUCTS)avl/avl_norme.c 			\
		$(SRC_DIR)$(DATA_STRUCTS)queue/queue.c 				\
		$(SRC_DIR)$(TOOLS)djb2.c





SRC_PRINTF += 	$(SRC_DIR)$(PRINTF)arguments.c 			\
				$(SRC_DIR)$(PRINTF)parse_arguments.c 	\
				$(SRC_DIR)$(PRINTF)floats.c 			\
				$(SRC_DIR)$(PRINTF)hand_base.c 			\
				$(SRC_DIR)$(PRINTF)hand_string.c 		\
				$(SRC_DIR)$(PRINTF)useful_functions.c 	\
				$(SRC_DIR)$(PRINTF)useful_functions_2.c	\
				$(SRC_DIR)$(PRINTF)ft_printf.c 			\
				$(SRC_DIR)$(PRINTF)hand_di.c 			\
				$(SRC_DIR)$(PRINTF)indentation.c 		\
				$(SRC_DIR)$(PRINTF)bonus.c 				\
				$(SRC_DIR)$(PRINTF)buff.c



OBJ += $(SRC:.c=.o)
OBJ += $(SRC_PRINTF:.c=.o)

all: $(NAME)
	@:

$(OBJ): %.o: %.c
	@printf $(ccyellow)"#"$(ccend)
	@$(CC) $(CFLAGS) -I $(HEADERS) -c $< -o $@

$(NAME): $(OBJ)
	@printf $(ccgreen)"\t[OK]\n"$(ccend)
	@ar rcs $(NAME) $(OBJ)
	@ranlib $(NAME)

clean:
	@/bin/rm -rf $(OBJ)

fclean: clean
	@/bin/rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
