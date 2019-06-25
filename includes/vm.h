#ifndef VM_H
# define VM_H

# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <limits.h>
# include <inttypes.h>
# include <ncurses.h>

# include "op.h"
# include "../libft/includes/libft.h"

# define S_BOLD "\e[001m"
# define E_BOLD "\e[0022m"

// TODO: add a FLAG_VERB
# define FLAG_ERROR (1 << 0)
# define FLAG_HELP (1 << 1)
# define FLAG_VISU (1 << 2)
# define FLAG_DUMP (1 << 3)

# define ERROR_MAX_VALUE 6

typedef enum	e_error
{
	ERROR_NONE,
	ERROR_SPE_NUMB,
	ERROR_SPE_DUMP,
	ERROR_CHAMPION,
	ERROR_SME_NUMB,
	ERROR_WRG_NUMB,
	ERROR_UNK_ARGV
}				t_error;

typedef char	t_flag;

t_op    op_tab[17]; // TODO: eclare variable as global here, should look up how
					// to do it properly using extern.

typedef struct s_player
{
	header_t			header;
	char				*file;
	int					number;
	int					parse_index;
	int					alive;
}				t_player;

typedef struct	s_argument
{
	unsigned char	type;
	int				value;
}				t_argument;

typedef struct	s_process
{
	int					regs[REG_NUMBER];
	t_argument			args[MAX_ARGS_NUMBER];
	int					pc;
	int					carry;
	int					alive;
	int					cycle;
	int					player;
	int					color;
	struct s_process 	*prev;
	struct s_process 	*next;
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
	int					error_value;
	int					last_live;
	char				*error_str[ERROR_MAX_VALUE + 1];
}				t_env;

/*
**	ENV
*/

void		init_env(t_env *env);
void		init_arena(t_env *e);
void		set_error_value(t_env *env, t_error value);
void		display_error(t_env *env);
void		display_help(t_env *env);

/*
**	MAIN LOOP
*/

void		game_loop(t_env *env);

/*
**	PROCESS
*/

t_process	*new_process(int player, int alive);
void		append_process(t_process **head, t_process *new_p);
void		delete_process(t_process **head, t_process *ptr);

/*
**	OP
*/

int		get_args_len(t_process *cursor, t_op op);
void	read_args(t_env *e, t_process *cursor, t_op op);
void	ft_live(t_env *e, t_process *cursor, t_op op);
void	ft_ld(t_env *e, t_process *cursor, t_op op);
void	ft_st(t_env *e, t_process *cursor, t_op op);
void	ft_add(t_env *e, t_process *cursor, t_op op);
void	ft_sub(t_env *e, t_process *cursor, t_op op);
void	ft_and(t_env *e, t_process *cursor, t_op op);
void	ft_or(t_env *e, t_process *cursor, t_op op);
void	ft_xor(t_env *e, t_process *cursor, t_op op);
void	ft_zjmp(t_env *e, t_process *cursor, t_op op);
void	ft_ldi(t_env *e, t_process *cursor, t_op op);
void	ft_sti(t_env *e, t_process *cursor, t_op op);
void	ft_fork(t_env *e, t_process *cursor, t_op op);
void	ft_lld(t_env *e, t_process *cursor, t_op op);
void	ft_lldi(t_env *e, t_process *cursor, t_op op);
void	ft_lfork(t_env *e, t_process *cursor, t_op op);
void	ft_aff(t_env *e, t_process *cursor, t_op op);

/*
**	PLAYER
*/

void		init_player(t_player *player);

/*
**	PARSING FILES
*/

void			print_arena(t_env *e);
void			read_files(t_env *e);

/*
**	ERROR HANDLING
*/

void			exit_vm(t_env *e, int status);
void			exit_failure(const char *message, t_env *e);

/*
**	PARSING_ARGS
*/

void		shift_args(t_env *env, t_process *cursor, int shift, int ind_mod);
void		parsing_args(char **av, int ac, t_env *env);

/*
**	UTILS
*/

int			posmod(int n, int mod);
int			ft_atoi_pimp(char *line, t_env *env);

/*
**	DEBBUGING
*/

void			d_display_env(t_env env);
void			d_display_process(t_process *pro);
void			d_display_full_process(t_env env);
void			d_display_argument(t_process *cursor, t_op op);

#endif
