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

void	ft_sti(t_env *e, t_process *cursor, t_op op)
{
	int		sum;

	read_args(e, cursor, op);
	DEBUG(d_display_argument(cursor, op))
	shift_args(e, cursor, 3, TRUE);
	sum = (cursor->args[1].value + cursor->args[2].value) % IDX_MOD;
	write_byte(cursor->regs[cursor->args[0].value], e, sum, cursor);
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
		cursor->pc = posmod(cursor->pc + get_args_len(cursor, op), MEM_SIZE);
	else
		cursor->pc = posmod(cursor->pc + get_args_len(cursor, op) + 1, MEM_SIZE);
}

void	ft_add(t_env *e, t_process *cursor, t_op op)
{
	int	res;

	read_args(e, cursor, op);
	DEBUG(d_display_argument(cursor, op))
	res = cursor->regs[cursor->args[0].value] + cursor->regs[cursor->args[1].value];
	cursor->regs[cursor->args[2].value] = res;
	cursor->carry = !res;
	SET_MSIZE(cursor->pc, get_args_len(cursor, op) + 1);
}

void	ft_sub(t_env *e, t_process *cursor, t_op op)
{
	int	res;

	read_args(e, cursor, op);
	DEBUG(d_display_argument(cursor, op))
	res = cursor->regs[cursor->args[0].value] - cursor->regs[cursor->args[1].value];
	cursor->regs[cursor->args[2].value] = res;
	cursor->carry = !res;
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
	int		res;

	read_args(e, cursor, op);
	DEBUG(d_display_argument(cursor, op))
	shift_args(e, cursor, 2, TRUE);
	res = cursor->args[0].value & cursor->args[1].value;
	cursor->regs[cursor->args[2].value] = res;
	cursor->carry = !res;
	SET_MSIZE(cursor->pc, get_args_len(cursor, op) + 1);
}

void	ft_or(t_env *e, t_process *cursor, t_op op)
{
	int	res;

	read_args(e, cursor, op);
	DEBUG(d_display_argument(cursor, op))
	shift_args(e, cursor, 2, TRUE);
	res = cursor->args[0].value | cursor->args[1].value;
	cursor->regs[cursor->args[2].value] = res;
	cursor->carry = !res;
	SET_MSIZE(cursor->pc, get_args_len(cursor, op) + 1);
}

void	ft_xor(t_env *e, t_process *cursor, t_op op)
{
	int	res;

	read_args(e, cursor, op);
	DEBUG(d_display_argument(cursor, op))
	shift_args(e, cursor, 2, TRUE);
	res = cursor->args[0].value ^ cursor->args[1].value;
	cursor->regs[cursor->args[2].value] = res;
	cursor->carry = !res;
	SET_MSIZE(cursor->pc, get_args_len(cursor, op) + 1);
}

void	ft_ld(t_env *e, t_process *cursor, t_op op)
{
	read_args(e, cursor, op);
	DEBUG(d_display_argument(cursor, op))
	shift_args(e, cursor, 1, TRUE);
	cursor->regs[cursor->args[1].value] = cursor->args[0].value;
	cursor->carry = !cursor->args[0].value;
	cursor->pc = posmod(cursor->pc + get_args_len(cursor, op) + 1, MEM_SIZE);
}

// i don't know what i'm doing here
void	ft_st(t_env *e, t_process *cursor, t_op op)
{
	read_args(e, cursor, op);
	if (cursor->args[0].type == T_IND)
		cursor->args[0].value += cursor->pc;
	cursor->regs[cursor->args[1].value] = cursor->args[0].value;
	cursor->pc = posmod(cursor->pc + get_args_len(cursor, op) + 1, MEM_SIZE);
}

#define SOMETHING 2 // we need to think and sleep

void	ft_ldi(t_env *e, t_process *cursor, t_op op)
{
	int		res;

	read_args(e, cursor, op);
	shift_args(e, cursor, 2, FALSE);
	res = posmod((cursor->args[0].value + cursor->args[1].value) % IDX_MOD, MEM_SIZE);
	
	cursor->regs[cursor->args[2].value] = mix_bytes(e, res, SOMETHING);
	cursor->pc = posmod(cursor->pc + get_args_len(cursor, op) + 1, MEM_SIZE);
}

void	ft_fork(t_env *e, t_process *cursor, t_op op)
{
	t_process	*child;

	child = new_process(cursor->player, cursor->alive);
	if (!child)
		exit_failure("Error: malloc failed in ft_fork", e);
	cpy_process(child, cursor);		// need to check if it's ok
	read_args(e, cursor, op);
	child->pc = posmod(cursor->pc + (cursor->regs[cursor->args[0].value] % IDX_MOD), MEM_SIZE); 
	append_process(&e->cursors, child);
	cursor->pc = posmod(cursor->pc + get_args_len(cursor, op) + 1, MEM_SIZE);
}

void	ft_lld(t_env *e, t_process *cursor, t_op op)
{
	read_args(e, cursor, op);
	DEBUG(d_display_argument(cursor, op))
	shift_args(e, cursor, 1, FALSE);
	cursor->regs[cursor->args[1].value] = cursor->args[0].value;
	cursor->carry = !cursor->args[0].value;
	cursor->pc = posmod(cursor->pc + get_args_len(cursor, op) + 1, MEM_SIZE);
}

void	ft_lldi(t_env *e, t_process *cursor, t_op op)
{
	int		res;

	read_args(e, cursor, op);
	shift_args(e, cursor, 2, FALSE);
	res = posmod(cursor->args[0].value + cursor->args[1].value, MEM_SIZE);
	cursor->regs[cursor->args[2].value] = mix_bytes(e, res, SOMETHING);
	cursor->pc = posmod(cursor->pc + get_args_len(cursor, op) + 1, MEM_SIZE);
}

void	ft_lfork(t_env *e, t_process *cursor, t_op op)
{
	t_process	*child;

	child = new_process(cursor->player, cursor->alive);
	if (!child)
		exit_failure("Error: malloc failed in ft_lfork", e);
	cpy_process(child, cursor);		// need to check if it's ok
	read_args(e, cursor, op);
	child->pc = posmod(cursor->pc + cursor->regs[cursor->args[0].value], MEM_SIZE); 
	append_process(&e->cursors, child);
	cursor->pc = posmod(cursor->pc + get_args_len(cursor, op) + 1, MEM_SIZE);
}

void	ft_aff(t_env *e, t_process *cursor, t_op op)
{
	read_args(e, cursor, op);
	DEBUG(d_display_argument(cursor, op))
	ft_putchar(cursor->regs[cursor->args[0].value] % 256);
	cursor->pc = posmod(cursor->pc + get_args_len(cursor, op) + 1, MEM_SIZE);
}
