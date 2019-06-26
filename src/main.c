#include "vm.h"

int		main(int ac, char **av)
{
	t_env		env;

	g_debug = 0;
	init_env(&env);
	parsing_args(av, ac, &env);
	read_files(&env);
	game_loop(&env);
	DEBUG(d_display_env(env))
	exit_vm(&env, EXIT_SUCCESS);
	return (0);
}
