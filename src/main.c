#include "../includes/vm.h"

int main(int ac, char **av)
{
	t_env		env;

	init_env(&env);
	parsing_args(av, ac, &env);
	d_display_env(env);
	read_files(&env);
	d_display_env(env);
	exit_vm(&env, EXIT_SUCCESS);
}
