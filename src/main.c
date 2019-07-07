#include "vm.h"
void		init_processes(t_env *env);

void	display_contestants(t_env *env)
{
	int		i;

	i = 0;
	ft_printf("Introducing contestants...\n");
	while (i < env->players_nb)
	{
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n"
			, env->players[i].number
			, env->players[i].header.prog_size
			, env->players[i].header.prog_name
			, env->players[i].header.comment);
		i++;
	}
}

int		main(int ac, char **av)
{
	t_env		env;

	g_debug = 0;
	init_env(&env);
	parsing_args(av, ac, &env);
	read_files(&env);
	init_processes(&env);
	if (env.verb >= VERB_AFF)
		display_contestants(&env);
	/* 
	if (env.verb >= VERB_DUMP_START)
	{
		ft_printf("Arena:\n");
		print_arena(&env);
	}
	*/
	game_loop(&env);
	DEBUG(d_display_env(env))
	exit_vm(&env, EXIT_SUCCESS);
	return (0);
}
