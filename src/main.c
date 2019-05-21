#include "../includes/vm.h"

int main(int ac, char **av)
{
	t_env		env;

	init_env(&env);
	parsing_args(av, ac, &env);
	return (0);
}
