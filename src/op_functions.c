#include "../includes/vm.h"

#define SET_MSIZE(where, x) where = (where + x) % MEM_SIZE
#define SET_MIDX(where, x) where = (where + (x % IDX_MOD)) % MEM_SIZE
#define MIDX(x) x % IDX_MOD
#define P_CURSOR_PC ft_printf("cursor->pc @ %d", cursor->pc); ft_putendl(0);
#define PRINT_D(x) ft_printf("%s: %d\n",#x, x);
#define OP_CODE_LEN 1

void	write_byte(t_env *e, int32_t addr, int32_t value, int32_t size)
{
	int8_t i;

	i = 0;
	while (size--)
	{
		e->arena[POSMOD(addr + size - 1)].data = (uint8_t)((value >> i) & 0xFF);
		i += 8;
		size--;
	}
}

void	int_to_bytecode(t_env *e, int addr, int value, int size)
{
	int8_t i;

	i = 0;
	while (size)
	{
		e->arena[POSMOD(addr + size - 1)].data = (uint8_t)((value >> i) & 0xFF);
		i += 8;
		size--;
	}
}

void	ft_live(t_env *e, t_process *cursor, t_op op)
{
	int i;

	i = 0;
	read_args(e, cursor, op);
	DEBUG(d_display_argument(cursor, op))
	cursor->alive += 1;
	while (i < e->players_nb)
	{
		if (e->players[i].number == cursor->args[0].value)
		{
			e->players[i].alive += 1;
			e->last_live = i;
			ft_printf("A process shows that player %d (%s) is alive\n", e->players[i].number, e->players[i].header.prog_name);
			break ;
		}
		++i;
	}
	cursor->pc = POSMOD(cursor->pc + get_args_len(cursor, op) + 1);
}

void	ft_sti(t_env *e, t_process *cursor, t_op op)
{
	int	addr;
	int	i;

	read_args(e, cursor, op);
	set_reg_values(cursor, op , -1);
	DEBUG(d_display_argument(cursor, op))
	i = -1;
	while (++i < op.param_nb)
	{
		if (cursor->args[i].type != T_IND)
			continue;
		cursor->args[i].value += cursor->pc;
	}
	addr = MODX(cursor->args[1].value + cursor->args[2].value);
	write_byte(e, cursor->pc + addr + OP_CODE_LEN, cursor->args[0].value, DIR_SIZE); // Adding the pc here makes it work but should we?
	cursor->pc = POSMOD(cursor->pc + get_args_len(cursor,op) + 1);
}

/*
** @function: ft_st
**
** @args: T_REG, T_IND | T_REG 
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
		int addr = cursor->pc + MODX(cursor->args[1].value);
		DEBUG(PRINT_D(addr))
		write_byte(e, addr + OP_CODE_LEN, cursor->args[0].value, DIR_SIZE);

	}
	else if( cursor->args[1].type == T_REG)
	{
		cursor->regs[cursor->args[1].value - 1] = cursor->args[0].value;
	}
	cursor->pc = POSMOD(cursor->pc + get_args_len(cursor, op) + OP_CODE_LEN);
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

void	ft_add(t_env *e, t_process *cursor, t_op op)
{
	int	res;

	read_args(e, cursor, op);
	DEBUG(d_display_argument(cursor, op))
	res = cursor->regs[cursor->args[0].value - 1] + cursor->regs[cursor->args[1].value - 1];
	cursor->regs[cursor->args[2].value - 1] = res;
	cursor->carry = !res;
	cursor->pc = posmod(cursor->pc + get_args_len(cursor, op) + 1, MEM_SIZE);
}

void	ft_sub(t_env *e, t_process *cursor, t_op op)
{
	int	res;

	read_args(e, cursor, op);
	DEBUG(d_display_argument(cursor, op))
	res = cursor->regs[cursor->args[0].value - 1] - cursor->regs[cursor->args[1].value - 1];
	cursor->regs[cursor->args[2].value - 1] = res;
	cursor->carry = !res;
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
	cursor->regs[cursor->args[2].value - 1] = res;
	cursor->carry = !res;
	cursor->pc = POSMOD(cursor->pc + get_args_len(cursor,op) + 1);
}

void	ft_or(t_env *e, t_process *cursor, t_op op)
{
	int		res;

	read_args(e, cursor, op);
	DEBUG(d_display_argument(cursor, op))
	shift_args(e, cursor, 2, TRUE);
	res = cursor->args[0].value | cursor->args[1].value;
	cursor->regs[cursor->args[2].value - 1] = res;
	cursor->carry = !res;
	cursor->pc = POSMOD(cursor->pc + get_args_len(cursor,op) + 1);
}

void	ft_xor(t_env *e, t_process *cursor, t_op op)
{
	int		res;

	read_args(e, cursor, op);
	DEBUG(d_display_argument(cursor, op))
	shift_args(e, cursor, 2, TRUE);
	res = cursor->args[0].value ^ cursor->args[1].value;
	cursor->regs[cursor->args[2].value - 1] = res;
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
	if (cursor->args[0].value == 0)
		cursor->carry = 1;
	else
		cursor->carry = 0;
	cursor->pc = POSMOD(cursor->pc + get_args_len(cursor,op) + 1);
}

void	ft_ldi(t_env *e, t_process *cursor, t_op op)
{
	int		res;

	read_args(e, cursor, op);
	shift_args(e, cursor, 2, FALSE);
	res = posmod(((cursor->args[0].value + cursor->args[1].value) % IDX_MOD) + cursor->pc, MEM_SIZE);
	cursor->regs[cursor->args[2].value - 1] = mix_bytes(e, cursor, res, DIR_SIZE);
	cursor->pc = posmod(cursor->pc + get_args_len(cursor, op) + 1, MEM_SIZE);
}

void	ft_fork(t_env *e, t_process *cursor, t_op op)
{
	t_process	*child;

	child = new_process(cursor->player, cursor->alive);
	if (!child)
		exit_failure("Error: malloc failed in ft_fork", e);
	cpy_process(child, cursor);
	read_args(e, cursor, op);
	child->pc = posmod(cursor->pc + (cursor->regs[cursor->args[0].value - 1] % IDX_MOD), MEM_SIZE); 
	append_process(&e->cursors, child);
	cursor->pc = posmod(cursor->pc + get_args_len(cursor, op) + 1, MEM_SIZE);
}

void	ft_lld(t_env *e, t_process *cursor, t_op op)
{
	return ;
}

void	ft_lldi(t_env *e, t_process *cursor, t_op op)
{
	int		res;

	read_args(e, cursor, op);
	shift_args(e, cursor, 2, FALSE);
	res = posmod(cursor->args[0].value + cursor->args[1].value + cursor->pc, MEM_SIZE);
	cursor->regs[cursor->args[2].value - 1] = mix_bytes(e, cursor, res, DIR_SIZE);
	cursor->pc = posmod(cursor->pc + get_args_len(cursor, op) + 1, MEM_SIZE);
}

void	ft_lfork(t_env *e, t_process *cursor, t_op op)
{
	t_process	*child;

	child = new_process(cursor->player, cursor->alive);
	if (!child)
		exit_failure("Error: malloc failed in ft_lfork", e);
	cpy_process(child, cursor);
	read_args(e, cursor, op);
	child->pc = posmod(cursor->pc + cursor->regs[cursor->args[0].value - 1], MEM_SIZE); 
	append_process(&e->cursors, child);
	cursor->pc = posmod(cursor->pc + get_args_len(cursor, op) + 1, MEM_SIZE);
}

void	ft_aff(t_env *e, t_process *cursor, t_op op)
{
	read_args(e, cursor, op);
	ft_putchar(cursor->regs[cursor->args[0].value - 1] % 256);
	cursor->pc = posmod(cursor->pc + get_args_len(cursor, op) + 1, MEM_SIZE);
}
