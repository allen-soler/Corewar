#include "../includes/vm.h"

void	ft_and(t_env *e, t_process *cursor, t_op op)
{
	int		res;

	set_reg_values(cursor, op, 2);
	charge_memory(e, cursor, op, TRUE);
	res = cursor->args[0].value & cursor->args[1].value;
	cursor->regs[cursor->args[2].value - 1] = res;
	cursor->carry = !res;
}

void	ft_fork(t_env *e, t_process *cursor, t_op op)
{
	t_process	*child;

	(void)op;
	(void)e;
	child = new_process(cursor->player, e->last_pid++);
	duplicate_process(child, cursor);
	child->pc = POSMOD(cursor->pc + MODX(cursor->args[0].value));
	push_process_front(&e->cursors, child);
	read_instruction(e, child, FALSE);
}

void	ft_lfork(t_env *e, t_process *cursor, t_op op)
{
	t_process	*child;

	(void)op;
	(void)e;
	child = new_process(cursor->player, e->last_pid++);
	duplicate_process(child, cursor);
	child->pc = POSMOD(cursor->pc + cursor->args[0].value);
	push_process_front(&e->cursors, child);
	read_instruction(e, child, FALSE);
}

void	ft_add(t_env *e, t_process *cursor, t_op op)
{
	int		res;

	(void)e;
	set_reg_values(cursor, op, 2);
	res = cursor->args[0].value + cursor->args[1].value;
	cursor->regs[cursor->args[2].value - 1] = res;
	cursor->carry = !res;
}

void	ft_sub(t_env *e, t_process *cursor, t_op op)
{
	int		res;

	(void)e;
	set_reg_values(cursor, op, 2);
	res = cursor->args[0].value - cursor->args[1].value;
	cursor->regs[cursor->args[2].value - 1] = res;
	cursor->carry = !res;
}
