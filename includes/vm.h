#ifndef VM_H
# define VM_H

# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <limits.h>

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
# define ERROR_SPE_NUMB 1
# define ERROR_SPE_DUMP 2
# define ERROR_CHAMPION 3
# define ERROR_SME_NUMB 4
# define ERROR_WRG_NUMB 5
# define ERROR_UNK_ARGV 6

typedef char	t_flag;

typedef struct s_player
{
	header_t			header;
	char				*file;
	int					number;
	int					parse_index;
}				t_player;

typedef struct	s_process
{
	int					regs[REG_NUMBER];
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
	char				data; 		// hexa value
	int					player;		// index based information, not player number (allespag: what ??)
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
	char				*error_str[ERROR_MAX_VALUE + 1];
}				t_env;

/*
**	ENV
*/

void		init_env(t_env *env);
void		init_arena(t_env *e);
void		set_error_value(t_env *env, int value);
void		display_error(t_env *env);
void		display_help(t_env *env);

/*
**	MAIN LOOP
*/

void		game_loop(t_env *env);

/*
**	PROCESS
*/

t_process	*new_process(int player);
void		append_process(t_process **head, t_process *new);
void		delete_process(t_process **head, t_process *ptr);

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

void		parsing_args(char **av, int ac, t_env *env);

/*
**	UTILS
*/

int			ft_atoi_pimp(char *line, t_env *env);

/*
**	DEBBUGING
*/

void			d_display_env(t_env env);
void			d_display_process(t_process *pro);
void			d_display_full_process(t_env env);

#endif
