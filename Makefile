# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jallen <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/13 09:04:38 by jallen            #+#    #+#              #
#    Updated: 2019/07/13 10:58:17 by jallen           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRC_VM =	args_utils.c	\
			exit_vm.c       \
			main.c          \
			op_utils.c      \
			ops2.c          \
			ops4.c          \
			parsing_flags.c \
			set_players.c   \
			t_loop.c        \
			utils.c			\
			display_info.c	\
			game_loop.c     \
			op.c            \
			ops1.c          \
			ops3.c          \
			parsing_args.c  \
			read_files.c    \
			t_env.c         \
			t_process.c

SRC_ASM =	check_args.c		\
			encoding.c          \
			free_systems.c      \
			instruct_tokens.c   \
			match_labels.c      \
			para_list.c         \
			second_half.c		\
			check_comma.c       \
			encoding_tools.c   	\
			handle_errors.c     \
			instruction_utils.c \
			null_state.c        \
			parsing_tools.c     \
			syntax_checker.c	\
			create_file.c       \
			first_half.c        \
			handle_labels.c     \
			main.c              \
			op.c                \
			search_point.c      \
			token_automata.c

OBJ_VM = $(SRC_VM:.c=.o)
OBJ_ASM = $(SRC_ASM:.c=.o)

SRCDIR_VM = srcs_vm/
SRCDIR_ASM = srcs_asm/

OBJDIR_VM = objs_vm/
OBJDIR_ASM = objs_asm/

LIBFT = libft/

SRCS_VM = $(addprefix $(SRCDIR_VM), $(SRC_VM))
OBJS_VM = $(addprefix $(OBJDIR_VM), $(OBJ_VM))

SRCS_ASM = $(addprefix $(SRCDIR_ASM), $(SRC_ASM))
OBJS_ASM = $(addprefix $(OBJDIR_ASM), $(OBJ_ASM))

ASM_HEADER = -I includes -I $(LIBFT)includes

CC = gcc
CFLAG = -c
WFLAG = -Wall -Wextra -Werror

VM = corewar
ASM = asm

H_FILES = includes/vm.h includes/op.h includes/asm.h

.PHONY: all $(CHAMP) clean fclean re
.SUFFIXES: .c .o .s .cor

all: $(VM) $(ASM) 

#COMPILING VIRTUAL MACHINE
$(OBJDIR_VM)%.o: $(SRCDIR_VM)%.c $(H_FILES)
	@/bin/mkdir -p $(OBJDIR_VM)
	@$(CC) $(CFLAG) $(WFLAG) $(VM_HEADER) $< -o $@

$(VM): $(OBJS_VM)
	@make -s -C $(LIBFT)
	@$(CC) $(OBJS_VM) $(LIBFT)libft.a -o $@
	@echo "\x1b[33;1m[$(VM)]\x1b[0m"
	@echo

#COMPILING ASSEMBLER
$(OBJDIR_ASM)%.o: $(SRCDIR_ASM)%.c $(H_FILES)
	@/bin/mkdir -p $(OBJDIR_ASM)
	@$(CC) $(CFLAG) $(WFLAG) $(ASM_HEADER) $< -o $@

$(ASM): $(OBJS_ASM)
	@make -s -C $(LIBFT)
	@$(CC) $(OBJS_ASM) $(LIBFT)libft.a -o $@
	@echo "\x1b[32;1m[$(ASM)]\x1b[0m"
	@echo

clean:
	@/bin/rm -rf $(OBJDIR_VM) $(OBJDIR_ASM)
	@make -s -C $(LIBFT) clean
	@echo "\x1b[35;1m[clean]\x1b[0m"
	@echo

fclean: clean
	@/bin/rm -rf $(VM) $(ASM) $(LIBFT)libft.a 
	@echo "\x1b[31;1m[fclean]\x1b[0m"
	@echo

re: fclean all
