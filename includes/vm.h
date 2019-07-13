/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalonso <nalonso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 10:10:05 by nalonso           #+#    #+#             */
/*   Updated: 2019/07/13 10:25:06 by nalonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <limits.h>
# include <inttypes.h>

# include "op.h"
# include "../libft/libft.h"

# define S_BOLD "\e[001m"
# define E_BOLD "\e[0022m"

# define FLAG_ERROR (1 << 0)
# define FLAG_HELP (1 << 1)
# define FLAG_VERB (1 << 2)
# define FLAG_DUMP (1 << 3)
# define FLAG_COLR (1 << 4)

# define ERROR_MAX_VALUE 8

# define MSIZE MEM_SIZE
# define ZMASK(x) ((x) & 0xff)
# define POSMOD(x) (((x) % MSIZE) < 0 ? ((x) % MSIZE) + MSIZE : (x) % MSIZE)
# define MODMS(x) ((x) % MEM_SIZE)
# define MODX(x) ((x) % IDX_MOD)
# define ABS(value)  ((value) > 0 ? (value) : -(value))

# define VERB(val, func) if (e->verb >= val) func
# define SHIFT(x) (1 << (x))

typedef enum	e_verb
{
	VERB_WINNER = 0,
	VERB_AFF = SHIFT(0),
	VERB_LIVE = SHIFT(1),
	VERB_PROCESS_CREATION_DEATH = SHIFT(2),
	VERB_SHOW_CYCLES = SHIFT(3),
}				t_verb;

typedef enum	e_bool
{
	FALSE,
	TRUE
}				t_bool;

t_bool	g_debug;
t_op	g_op_tab[17];

typedef enum	e_error
{
	ERROR_NONE,
	ERROR_SPE_NUMB,
	ERROR_SPE_DUMP,
	ERROR_CHAMPION,
	ERROR_SME_NUMB,
	ERROR_WRG_NUMB,
	ERROR_SPE_LEVL,
	ERROR_WRG_LEVL,
	ERROR_UNK_ARGV
}				t_error;

typedef char	t_flag;

typedef struct	s_player
{
	t_header			header;
	char				*file;
	int					number;
	int					parse_index;
	int					alive;
	int					death;
}				t_player;

typedef struct	s_argument
{
	unsigned char		type;
	int					value;
}				t_argument;

typedef struct	s_process
{
	int					regs[REG_NUMBER];
	t_argument			args[MAX_ARGS_NUMBER];
	char				*verb_string;
	int					op_code;
	int					pc;
	int					pid;
	int					carry;
	int					alive;
	int					cycle;
	int					player;
	int					color;
	int					a_len;
	struct s_process	*next;
}				t_process;

typedef struct	s_arena
{
	char				data;
	int					player;
}				t_arena;

typedef struct	s_loop
{
	int			nb_process_alive;
	int			current_cycle;
	int			i_cycle;
	int			i_check;
	int			cycle_last_check;
	int			cycle_to_die;
}				t_loop;

typedef struct	s_env
{
	t_player			players[MAX_PLAYERS];
	t_arena				arena[MEM_SIZE];
	t_process			*cursors;
	int					players_nb;
	t_flag				flag;
	int					dump;
	int					n_dump;
	int					last_pid;
	int					error_value;
	t_verb				verb;
	int					last_live;
	char				*error_str[ERROR_MAX_VALUE + 1];
}				t_env;

/*
**	ENV
*/

void			init_env(t_env *env);
void			set_error_value(t_env *env, t_error value);
void			display_error(t_env *env);

/*
**	MAIN LOOP
*/

void			init_loop(t_loop *loop);
void			init_processes(t_env *env);
void			game_loop(t_env *env);

/*
**	PROCESS
*/

t_process		*new_process(int player, int pid);
void			duplicate_process(t_process *dst, t_process *src);
void			append_process(t_process **head, t_process *new_p);
void			delete_process(t_process **head, t_process *ptr);
void			push_process_front(t_process **head, t_process *new);
void			init_processes(t_env *env);

/*
** ARGUMENT UTILS
*/

int				mix_bytes(t_env *e, t_process *cursor, int offset, int bytes);
int				get_args_len(t_process *cursor, t_op op);
void			shift_args(t_env *env,\
				t_process *cursor, int shift, t_bool ind_mod);
int				read_args(t_env *e, t_process *cursor, t_op op);
void			set_reg_values(t_process *cursor, t_op op, int skip_index);
void			read_instruction(t_env *e, t_process *cursor, t_bool move_pc);
void			charge_memory(t_env *e, t_process *proc, t_op op, t_bool modx);
void			write_byte(t_env *e, int32_t addr, int32_t value, int32_t size);

/*
** DISPLAY INFO
*/
void			display_help(t_env *env);
void			display_contestants(t_env *env);
void			print_arena(t_env *e);
void			print_winner(t_env *env);

/*
**	OP
*/

void			ft_live(t_env *e, t_process *cursor, t_op op);
void			ft_ld(t_env *e, t_process *cursor, t_op op);
void			ft_st(t_env *e, t_process *cursor, t_op op);
void			ft_add(t_env *e, t_process *cursor, t_op op);
void			ft_sub(t_env *e, t_process *cursor, t_op op);
void			ft_and(t_env *e, t_process *cursor, t_op op);
void			ft_or(t_env *e, t_process *cursor, t_op op);
void			ft_xor(t_env *e, t_process *cursor, t_op op);
void			ft_zjmp(t_env *e, t_process *cursor, t_op op);
void			ft_ldi(t_env *e, t_process *cursor, t_op op);
void			ft_sti(t_env *e, t_process *cursor, t_op op);
void			ft_fork(t_env *e, t_process *cursor, t_op op);
void			ft_lld(t_env *e, t_process *cursor, t_op op);
void			ft_lldi(t_env *e, t_process *cursor, t_op op);
void			ft_lfork(t_env *e, t_process *cursor, t_op op);
void			ft_aff(t_env *e, t_process *cursor, t_op op);

/*
**	PLAYER
*/

void			init_player(t_player *player);

/*
**	PARSING FILES
*/

void			read_files(t_env *e);

/*
**	ERROR HANDLING
*/

void			set_error_exit(t_env *e, t_error value);
void			exit_vm(t_env *e, int status);
void			exit_failure(const char *message, t_env *e);

/*
**	PARSING_ARGS
*/

int				choose_turn(int used, t_env *env);
int				set_player_turn(char **av, int ac, int index, t_env *env);
void			set_players(char **av, int ac, int i, t_env *env);
int				set_flag(char **av, int ac, t_env *env);
void			parsing_args(char **av, int ac, t_env *env);

/*
**	UTILS
*/

int				posmod(int n, int mod);
int				ft_atoi_pimp(char *line, t_env *env);
void			free_processes(t_process *head);
int				ft_endswith(const char *str, const char *suffix);

#endif
