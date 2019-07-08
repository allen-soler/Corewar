#include "vm.h"

void			set_error_value(t_env *env, t_error value)
{
	if (!(env->flag & FLAG_ERROR))
	{
		env->error_value = value;
		env->flag |= FLAG_ERROR;
	}
}

void			display_error(t_env *env)
{
	if (env->error_value > ERROR_MAX_VALUE)
		ft_fprintf(2, "{red}Error<rst>: There is an error with the error value...\n");
	ft_fprintf(2, "{red}Error<rst>: %s\n\n", env->error_str[env->error_value]);
	display_help(env);
}

static void 	init_arena(t_env *e)
{
	size_t 		i;

	i = 0;
	while (i < MEM_SIZE)
	{
		e->arena[i].player = -1;
		e->arena[i].data = 0;
		i += 1;
	}
}

// someone has to check if english is good here :(
static void		init_env_error(t_env *env)
{
	env->error_str[0] = "There is no problem, how can you read this ?";
	env->error_str[1] = "There is no specify number value after -n";
	env->error_str[2] = "There is no specify dump value after --dump";
	env->error_str[3] = "You can not use more than 4 champions";
	env->error_str[4] = "You can not set 2 players with the same number";
	env->error_str[5] = "Players turn can only be from 0 to 4";
	env->error_str[6] = "There is no specify verbosity value after --verbose";
	env->error_str[7] = "Verbosity level can only be from 0 to 7";
	env->error_str[8] = "unknown argv";				// we need to modify this
}

void		init_env(t_env *env)
{
	int		i;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		env->players[i].parse_index = -1;
		env->players[i].file = NULL;
		i++;
	}
	env->players_nb = 0;
	env->flag = 0;
	env->last_live = -1;
	env->dump = -1;
	env->n_dump = 32;
	env->error_value = 0;
	env->last_pid = 0;
	env->verb = VERB_LIVE;
	init_arena(env);
	init_env_error(env);
	env->cursors = NULL;
}
