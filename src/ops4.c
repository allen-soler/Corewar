#include "../includes/vm.h"

void	ft_aff(t_env *e, t_process *cursor, t_op op)
{
	char		c;

	c = cursor->regs[cursor->args[0].value - 1] % 256;
	VERB(VERB_AFF, ft_printf("aff: %c\n", c));
}
