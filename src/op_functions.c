#include "../includes/vm.h"

#define SET_MSIZE(where, x) where = (where + x) % MEM_SIZE
#define SET_MIDX(where, x) where = (where + (x % IDX_MOD)) % MEM_SIZE
#define MIDX(x) x % IDX_MOD
#define P_CURSOR_PC(where) ft_printf("cursor->pc @ %d", where); ft_putendl(0);

void	ft_live(t_env *e, t_process *cursor, t_op op)
{
	int i;

	i = 0;
	read_args(e, cursor, op);
	cursor->alive += 1;
	while (i < e->players_nb)
	{
		if (e->players[i].number == cursor->args[0].value)
		{
			e->players[i].alive += 1;
			e->last_live = i;
			break ;
		}
		++i;
	}
	SET_MSIZE(cursor->pc, get_args_len(cursor, op) + 1);
}

void	ft_sti(t_env *e, t_process *cursor, t_op op)
{
	int	i;
	int				pointer;

	read_args(e, cursor, op);
	d_display_argument(cursor, op);
	set_reg_values(cursor, op, 0);
	pointer = 0;
	i = 1;
	while (i < op.param_nb)
	{
		if (cursor->args[i].type == T_IND)
			pointer += cursor->pc;
		pointer += cursor->args[i].value;
		i += 1;
	}

	pointer += 4; // There is something that I'm missing here

	pointer = MIDX(pointer);

	e->arena[pointer - 1].data = cursor->regs[cursor->args[0].value - 1];
	e->arena[pointer - 1].player = 3;
	SET_MSIZE(cursor->pc, get_args_len(cursor, op) + 1);
}

/*
** @function: ft_and
** 
** @args: Takes 3 registers as parameter where the value
** contained in the first 2 registers are added and
** stored in the 3 parameter.
**
** This op code does a bitwise 'and' operation 'a & b'.
** If after the operation the register in question has the
** value 0, then the carry will be set to 1, 0 otherwise.
**
*/ 

void	ft_and(t_env *e, t_process *cursor, t_op op)
{
	int i;

	i = 0;
	read_args(e, cursor, op);
	d_display_argument(cursor, op);
	set_reg_values(cursor, op, 2);
	cursor->regs[cursor->args[2].value] = cursor->args[0].value & cursor->args[1].value;
	ft_printf("Register %d now has the value %d\n", cursor->args[2].value,\
			cursor->regs[cursor->args[2].value]);
	if (cursor->regs[cursor->args[2].value] == 0)
		cursor->carry = 1;
	else
		cursor->carry = 0;
	SET_MSIZE(cursor->pc, get_args_len(cursor, op) + 1);
}

/*
** @function: ft_zjmp
**
** @arg: one argument of type T_DIR and no encoding byte
**
** This op code, moves the cursor->pc to the position indicated
** in the argument, ONLY if the carry is equal to 1
*/ 

void	ft_zjmp(t_env *e, t_process *cursor, t_op op)
{
	read_args(e, cursor, op);
	d_display_argument(cursor, op);
	if (cursor->carry == 1)
	{
		SET_MIDX(cursor->pc, cursor->args[0].value);
	}
}

void	ft_add(t_env *e, t_process *cursor, t_op op)
{
	int	res;

	read_args(e, cursor, op);
	d_display_argument(cursor, op);
	set_reg_values(cursor, op, 2);
	res = cursor->regs[cursor->args[0].value] + cursor->regs[cursor->args[1].value];
	cursor->regs[cursor->args[2].value] = res;
	cursor->carry = !res;
	SET_MSIZE(cursor->pc, get_args_len(cursor, op) + 1);
}

void	ft_sub(t_env *e, t_process *cursor, t_op op)
{
	int	res;

	read_args(e, cursor, op);
	d_display_argument(cursor, op);
	set_reg_values(cursor, op, 2);
	res = cursor->regs[cursor->args[0].value] - cursor->regs[cursor->args[1].value];
	cursor->regs[cursor->args[2].value] = res;
	cursor->carry = !res;
	SET_MSIZE(cursor->pc, get_args_len(cursor, op) + 1);
}

void	ft_or(t_env *e, t_process *cursor, t_op op)
{
	int	res;

	read_args(e, cursor, op);
	d_display_argument(cursor, op);
	set_reg_values(cursor, op, 2);
	res = cursor->args[0].value | cursor->args[1].value;
	cursor->regs[cursor->args[2].value] = res;
	cursor->carry = !res;
	SET_MSIZE(cursor->pc, get_args_len(cursor, op) + 1);
}

void	ft_xor(t_env *e, t_process *cursor, t_op op)
{
	int	res;

	read_args(e, cursor, op);
	d_display_argument(cursor, op);
	set_reg_values(cursor, op, 2);
	res = cursor->args[0].value ^ cursor->args[1].value;
	cursor->regs[cursor->args[2].value] = res;
	cursor->carry = !res;
	SET_MSIZE(cursor->pc, get_args_len(cursor, op) + 1);
}

void	ft_ld(t_env *e, t_process *cursor, t_op op)
{
	return ;
}

void	ft_st(t_env *e, t_process *cursor, t_op op)
{
	return ;
}

void	ft_ldi(t_env *e, t_process *cursor, t_op op)
{
	return ;	
}
void	ft_fork(t_env *e, t_process *cursor, t_op op)
{
	return ;
}

void	ft_lld(t_env *e, t_process *cursor, t_op op)
{
	return ;
}

void	ft_lldi(t_env *e, t_process *cursor, t_op op)
{
	return ;
}

void	ft_lfork(t_env *e, t_process *cursor, t_op op)
{
	return ;
}

void	ft_aff(t_env *e, t_process *cursor, t_op op)
{
	return ;
}
