#include "vm.h"

void		init_env(t_env *env)
{
	int		i;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		env->players[i].parse_index = -1;
		i++;
	}
	env->flag = 0;
	env->dump = -1;
}
