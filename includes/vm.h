#ifndef VM_H
# define VM_H

# include <stdlib.h>
# include <limits.h>

# include "op.h"
# include "../libft/includes/libft.h"

# define S_BOLD "\e[001m"
# define E_BOLD "\e[0022m"

# define FLAG_ERROR (1 << 0)
# define FLAG_HELP (1 << 1)
# define FLAG_VISU (1 << 2)
# define FLAG_DUMP (1 << 3)

typedef char	t_flag;

typedef struct s_player
{
	header_t	header;
	int			parse_index;
}				t_player;

typedef struct	s_env
{
	t_player	players[MAX_PLAYERS];
//	t_arena		arena;
	char		**file;
	t_flag		flag;
	int			dump;
}				t_env;

/*
**	ENV
*/
void		init_env(t_env *env);

/*
**	PLAYER
*/
void		init_player(t_player *player);

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
void		d_display_env(t_env env);

#endif
