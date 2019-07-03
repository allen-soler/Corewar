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
		uint8_t tmp = ZMASK((value >> i));
		uint16_t ptr = POSMOD(addr + size - 1);
		e->arena[ptr].data = tmp;
		//e->arena[POSMOD(addr + size - 1)].player = 3;
		i += 8;
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
			VERB(VERB_OP, ft_printf("\n"));
			VERB(VERB_LIVE,\
					ft_printf("A process shows that player %d (%s) is alive%s",\
						e->players[i].number, e->players[i].header.prog_name,
						(e->verb < VERB_OP) ? "\n" : ""));
			e->last_live = i;
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
	write_byte(e, cursor->pc + addr + OP_CODE_LEN, cursor->args[0].value, DIR_SIZE);
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
	//DEBUG(d_display_argument(cursor, op))
	if (cursor->args[1].type == T_IND)
	{
		int addr = cursor->pc + MODX(cursor->args[1].value);
		//DEBUG(PRINT_D(addr))
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
	//DEBUG(d_display_argument(cursor, op))
	if (cursor->carry)
	{
		cursor->pc = POSMOD(cursor->pc + (cursor->args[0].value % IDX_MOD));
		VERB(VERB_OP, ft_printf(" OK"));
	}
	else
	{
		cursor->pc = POSMOD(cursor->pc + get_args_len(cursor, op) + 1);
		VERB(VERB_OP, ft_printf(" FAILED"));
	}

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
	//DEBUG(d_display_argument(cursor, op))
	set_reg_values(cursor, op, 2);
	res = cursor->args[0].value & cursor->args[1].value;
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
	//DEBUG(d_display_argument(cursor, op))
	if (cursor->args[0].type == T_IND)
		cursor->args[0].value = e->arena[POSMOD(cursor->pc + MODX(cursor->args[0].value))].data;
	cursor->regs[cursor->args[1].value - 1] = cursor->args[0].value;
	if (cursor->args[0].value == 0)
		cursor->carry = 1;
	else
		cursor->carry = 0;
	cursor->pc = POSMOD(cursor->pc + get_args_len(cursor,op) + 1);
}

/*
** @function: ft_fork
**
** @args: T_DIR
**
** Takes an address as a parameter, it will copy the process except
** the number of lives and the pc, that will be set to the
** specified values.
**
*/

void	ft_fork(t_env *e, t_process *cursor, t_op op)
{
	t_process	*child;

	read_args(e, cursor, op);
	child = new_process(cursor->player, cursor->alive, e->last_pid++);
	duplicate_process(child, cursor);
	child->pc = POSMOD(cursor->pc + MODX(cursor->args[0].value));
	push_process_front(&e->cursors, child);
	cursor->pc = POSMOD(cursor->pc + get_args_len(cursor, op) + OP_CODE_LEN);
	VERB(VERB_OP, ft_printf(" (%d)", child->pc));
}

void	ft_add(t_env *e, t_process *cursor, t_op op)
{
	int		res;

	read_args(e, cursor, op);
	res = cursor->regs[cursor->args[0].value - 1] + cursor->regs[cursor->args[1].value - 1];
	cursor->regs[cursor->args[2].value - 1] = res;
	cursor->carry = !res;
	cursor->pc = POSMOD(cursor->pc + get_args_len(cursor, op) + OP_CODE_LEN);
}

void	ft_sub(t_env *e, t_process *cursor, t_op op)
{
	int		res;

	set_reg_values(cursor, op, 2);
	read_args(e, cursor, op);
	res = cursor->args[0].value - cursor->args[1].value;
	cursor->regs[cursor->args[2].value - 1] = res;
	cursor->carry = !res;
	cursor->pc = POSMOD(cursor->pc + get_args_len(cursor, op) + OP_CODE_LEN);
}
void	ft_or(t_env *e, t_process *cursor, t_op op)
{
	int		res;

	read_args(e, cursor, op);
	//DEBUG(d_display_argument(cursor, op))
	set_reg_values(cursor, op, 2);
	res = cursor->args[0].value | cursor->args[1].value;
	cursor->regs[cursor->args[2].value - 1] = res;
	cursor->carry = !res;
	cursor->pc = POSMOD(cursor->pc + get_args_len(cursor,op) + 1);
}

void	ft_xor(t_env *e, t_process *cursor, t_op op)
{
	int		res;

	read_args(e, cursor, op);
	//DEBUG(d_display_argument(cursor, op))
	set_reg_values(cursor, op, 2);
	res = cursor->args[0].value ^ cursor->args[1].value;
	cursor->regs[cursor->args[2].value - 1] = res;
	cursor->carry = !res;
	cursor->pc = POSMOD(cursor->pc + get_args_len(cursor,op) + 1);
}

void	ft_ldi(t_env *e, t_process *cursor, t_op op)
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
	read_args(e, cursor, op);
	ft_putchar(cursor->regs[cursor->args[0].value - 1] % 256);
	cursor->pc = POSMOD(cursor->pc + get_args_len(cursor, op) + 1);
}
