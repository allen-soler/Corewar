#include "../includes/vm.h"

void	ft_or(t_env *e, t_process *cursor, t_op op)
{
	int		res;

	set_reg_values(cursor, op, 2);
	charge_memory(e, cursor, op, TRUE);
	res = cursor->args[0].value | cursor->args[1].value;
	cursor->regs[cursor->args[2].value - 1] = res;
	cursor->carry = !res;
}

void	ft_xor(t_env *e, t_process *cursor, t_op op)
{
	int		res;

	set_reg_values(cursor, op, 2);
	charge_memory(e, cursor, op, TRUE);
	res = cursor->args[0].value ^ cursor->args[1].value;
	cursor->regs[cursor->args[2].value - 1] = res;
	cursor->carry = !res;
}

void	ft_ldi(t_env *e, t_process *cursor, t_op op)
{
	int		addr;

	set_reg_values(cursor, op, 2);
	charge_memory(e, cursor, op, TRUE);
	addr = MODX(cursor->args[0].value + cursor->args[1].value);
	cursor->regs[cursor->args[2].value - 1] = mix_bytes(e, cursor, addr, 4);
}

void	ft_lld(t_env *e, t_process *cursor, t_op op)
{
	set_reg_values(cursor, op, 1);
	charge_memory(e, cursor, op, FALSE);
	cursor->regs[cursor->args[1].value - 1] = cursor->args[0].value;
	if (cursor->args[0].value == 0)
		cursor->carry = 1;
	else
		cursor->carry = 0;
}

void	ft_lldi(t_env *e, t_process *cursor, t_op op)
{
	int		addr;

	set_reg_values(cursor, op, 2);
	charge_memory(e, cursor, op, FALSE);
	addr = cursor->args[0].value + cursor->args[1].value;
	cursor->regs[cursor->args[2].value - 1] = mix_bytes(e, cursor, addr, 4);
}
