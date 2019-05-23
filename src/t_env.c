#include "vm.h"

void		set_error_value(t_env *env, int value)
{
	if (!(env->flag & FLAG_ERROR))
		env->error_value = value;
}

void		display_error(t_env *env)
{
	if (env->error_value > ERROR_MAX_VALUE)
		ft_fprintf(2, "{r}Error{R}: There is an error with the error value...\n");
	ft_fprintf(2, "{r}Error{R}: %s\n\n", env->error_str[env->error_value]);
	display_help(env);
}

void init_arena(t_env *e)
{
	size_t i;

	i = 0;
	while (i < MEM_SIZE)
	{
		e->arena[i].player = -1;
		e->arena[i].data = 0;
		i += 1;
	}
}

static void	init_env_error(t_env *env)
{
	env->error_str[0] = "There is no problem, how can you read this ?";
	env->error_str[1] = "You need to specify a number (1..4) after -n";
	env->error_str[2] = "There is no specify dump value after -dump";
	env->error_str[3] = "You can not use more than 4 champions";
	env->error_str[4] = "You can not set 2 players with the same number";
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
	env->dump = -1;
	env->error_value = 0;
	init_arena(env);
	init_env_error(env);
}
