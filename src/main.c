#include "vm.h"

void	testamos(t_env env)
{
	t_process	*pedro = new_process(5);
	t_process	*pablo = new_process(7);
	t_process	*jesus = new_process(9);

	pedro->alive = 0;
	pablo->alive = 0;
	jesus->alive = 0;
	append_process(&(env.cursors), pedro);
	append_process(&(env.cursors), pablo);
	append_process(&(env.cursors), jesus);
	d_display_full_process(env);
	check_live(env);
	d_display_full_process(env);
}

int		main(int ac, char **av)
{
	t_env		env;

	init_env(&env);
	parsing_args(av, ac, &env);
	read_files(&env);
	d_display_env(env);

	// on test des choses
		testamos(env);

	exit_vm(&env, EXIT_SUCCESS);
	return (0);
}
