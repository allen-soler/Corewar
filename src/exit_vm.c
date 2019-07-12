#include "../includes/vm.h"

void	exit_vm(t_env *e, int status)
{
	exit(status);
}

void	exit_failure(const char *message, t_env *e)
{
	ft_fprintf(2, "%s\n", message);
	exit_vm(e, EXIT_FAILURE);
}
