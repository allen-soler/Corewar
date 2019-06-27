#include "../includes/vm.h"

#define SET_MSIZE(where, x) where = (where + x) % MEM_SIZE
#define SET_MIDX(where, x) where = (where + (x % IDX_MOD)) % MEM_SIZE
#define MIDX(x) x % IDX_MOD
#define P_CURSOR_PC(where) ft_printf("cursor->pc @ %d", where); ft_putendl(0);

void	write_byte(long value, t_env *e, long number, t_process *process)
{
	int		byte;
	long	mult;
	int		i;

	i = 0;
	mult = 256L * 256L * 256L;
	if (value < 0)
		value = mult * 256L + value;
	while (i < 4)
	{
		byte = value / mult;
		e->arena[posmod(process->pc + number + i, MEM_SIZE)].data = byte;
		value -= byte * mult;
		mult /= 256L;
		i++;
	}
}


void	ft_live(t_env *e, t_process *cursor, t_op op)
{
	int i;

	i = 0;
	read_args(e, cursor, op);
	//DEBUG(d_display_argument(cursor, op))
	cursor->alive += 1;
	while (i < e->players_nb)
	{
		if (e->players[i].number == cursor->args[0].value)
		{
			e->players[i].alive += 1;
			DEBUG(ft_printf("Player %d(%s) is alive!\n", e->players[i].number, e->players[i].header.prog_name))
			e->last_live = i;
			break ;
		}
		++i;
	}
	cursor->pc = POSMOD(cursor->pc + get_args_len(cursor, op) + 1);
}

void	ft_sti(t_env *e, t_process *cursor, t_op op)
{
	int	sum;
	int	i;

	read_args(e, cursor, op);
	set_reg_values(cursor, op , 0);
	DEBUG(d_display_argument(cursor, op))
	i = -1;
	while (++i < op.param_nb)
	{
		if (cursor->args[i].type != T_IND)
			continue;
		cursor->args[i].value += cursor->pc;
	}
	sum = MODX(cursor->args[1].value + cursor->args[2].value);
	write_byte(cursor->regs[cursor->args[0].value - 1], e, sum, cursor);
	cursor->pc = POSMOD(cursor->pc + get_args_len(cursor,op) + 1);
}

/*
** @function: ft_st
**
** @args: two arguments, a value and a register or address where we'll
** store the value.
**
** This instruction saves the first parameter to a memory address or a
** register, depending of the second parameter
**
** Example: st r1 42, will save the value in r1 to (PC + (42 % IDX_MOD)
*/ 

void	ft_st(t_env *e, t_process *cursor, t_op op)
{
	read_args(e, cursor, op);
	set_reg_values(cursor, op, 1);
	DEBUG(d_display_argument(cursor, op))
	if (cursor->args[1].type == T_IND)
	{
		int pos = POSMOD(cursor->pc + MIDX(cursor->args[1].value));
		write_byte(cursor->args[0].value, e, pos, cursor);
	}
	else if( cursor->args[1].type == T_REG)
	{
		cursor->regs[cursor->args[1].value - 1] = cursor->args[0].value;
	}
	cursor->pc = posmod(cursor->pc + get_args_len(cursor, op) + 1, MEM_SIZE);
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
	DEBUG(d_display_argument(cursor, op))
	if (cursor->carry)
		cursor->pc = posmod(cursor->pc + (cursor->args[0].value % IDX_MOD), MEM_SIZE);
	else
		cursor->pc = posmod(cursor->pc + get_args_len(cursor, op) + 1, MEM_SIZE);
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
	int		res;

	read_args(e, cursor, op);
	DEBUG(d_display_argument(cursor, op))
	shift_args(e, cursor, 2, TRUE);
	res = cursor->args[0].value & cursor->args[1].value;
	cursor->regs[cursor->args[2].value] = res;
	cursor->carry = !res;
	cursor->pc = POSMOD(cursor->pc + get_args_len(cursor,op) + 1);
}

/*
** @function: ft_ld
**
** @args: T_IND | T_DIR, T_REG
**
** Load the value of the first argument into the registry
** 
** MODIFIES CARRY
**
*/ 

void	ft_ld(t_env *e, t_process *cursor, t_op op)
{
	read_args(e, cursor, op);
	set_reg_values(cursor, op, 1);
	DEBUG(d_display_argument(cursor, op))
	if (cursor->args[0].type == T_IND)
		cursor->args[0].value = e->arena[POSMOD(cursor->pc + MODX(cursor->args[0].value))].data;
	cursor->regs[cursor->args[1].value - 1] = cursor->args[0].value;
	if (cursor->args[0].value)
		cursor->carry = 1;
	else
		cursor->carry = 0;
	cursor->pc = POSMOD(cursor->pc + get_args_len(cursor,op) + 1);
}

void	ft_add(t_env *e, t_process *cursor, t_op op)
{
	return ;
}

void	ft_sub(t_env *e, t_process *cursor, t_op op)
{
	return ;
}
void	ft_or(t_env *e, t_process *cursor, t_op op)
{
	return ;
}

void	ft_xor(t_env *e, t_process *cursor, t_op op)
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
