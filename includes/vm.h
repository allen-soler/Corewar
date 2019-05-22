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

# define FLAG_ERROR (1 << 0)
# define FLAG_HELP (1 << 1)
# define FLAG_VISU (1 << 2)
# define FLAG_DUMP (1 << 3)

# define ERROR_MAX_VALUE 4

typedef char	t_flag;

typedef struct s_player
{
	header_t	header;
	char		*file;
	int			number;
	int			parse_index;
}				t_player;

typedef struct	s_env
{
	t_player	players[MAX_PLAYERS];
	char		arena[MEM_SIZE];
	int			players_nb;
	t_flag		flag;
	int			dump;
	int			error_value;
	char		*error_str[ERROR_MAX_VALUE + 1];
}				t_env;

/*
**	ENV
*/

void		init_env(t_env *env);
void		display_error(t_env *env);
void		display_help(t_env *env);

/*
**	PLAYER
*/

void		init_player(t_player *player);

/*
**	PARSING FILES
*/

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

#endif
