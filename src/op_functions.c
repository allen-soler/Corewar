#include "../includes/vm.h" 

void	charge_memory(t_env *e, t_process *proc, t_op op, t_bool modx)
{
	int8_t i;

	i = -1; 
	while (++i < op.param_nb)
	{
		if (proc->args[i].type != T_IND)
			continue ;
		if (modx)
			proc->args[i].value = mix_bytes(e, proc, proc->args[i].value % IDX_MOD, 4);
		else
			proc->args[i].value = mix_bytes(e, proc, proc->args[i].value, 4);
	}
}

void	write_byte(t_env *e, int32_t addr, int32_t value, int32_t size)
{
	int8_t i;
	uint8_t *r;

	i = 0;
	r = (uint8_t*)&value;
	DEBUG(ft_printf("writing value: %d, @ cursor->pc: %x\n", value, addr))
	while (size--)
	{
		uint16_t ptr = POSMOD(addr + (size - 1));
		e->arena[ptr].data = r[i];
		i += 1;
	}
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
	set_reg_values(cursor, op, 1);
	charge_memory(e, cursor, op, TRUE);
	cursor->regs[cursor->args[1].value - 1] = cursor->args[0].value;
	if (cursor->args[0].value == 0)
		cursor->carry = 1;
	else
		cursor->carry = 0;
}


void	ft_live(t_env *e, t_process *cursor, t_op op)
{
	int i;

	i = 0;
	while (i < e->players_nb)
	{
		if (e->players[i].number == cursor->args[0].value)
		{
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
	cursor->alive++;
}

void	ft_sti(t_env *e, t_process *cursor, t_op op)
{
	int	addr;

	set_reg_values(cursor, op , -1);
	charge_memory(e, cursor, op, TRUE);
	addr = cursor->pc + MODX(cursor->args[1].value + cursor->args[2].value);
	write_byte(e, addr + OP_CODE_LEN, cursor->args[0].value, DIR_SIZE);
}

void	ft_st(t_env *e, t_process *cursor, t_op op)
{
	if (cursor->args[1].type == T_IND)
	{
		int addr = cursor->pc + MODX(cursor->args[1].value);
		write_byte(e, addr + OP_CODE_LEN, cursor->regs[cursor->args[0].value - 1], DIR_SIZE);

	}
	else if( cursor->args[1].type == T_REG)
	{
		cursor->regs[cursor->args[1].value - 1] = cursor->regs[cursor->args[0].value - 1];
	}
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
	if (cursor->carry)
	{
		cursor->a_len = cursor->args[0].value % IDX_MOD;
		VERB(VERB_OP, ft_printf(" OK"));
	}
	else
		VERB(VERB_OP, ft_printf(" FAILED"));
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

	//DEBUG(d_display_argument(cursor, op))
	set_reg_values(cursor, op, 2);
	charge_memory(e, cursor, op, TRUE); // NOIDEA
	res = cursor->args[0].value & cursor->args[1].value;
	cursor->regs[cursor->args[2].value - 1] = res;
	cursor->carry = !res;
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

	child = new_process(cursor->player, cursor->alive, e->last_pid++);
	duplicate_process(child, cursor);
	child->pc = POSMOD(cursor->pc + MODX(cursor->args[0].value));
	VERB(VERB_OP, ft_printf(" (%d)", child->pc));
	push_process_front(&e->cursors, child);
	read_instruction(e, child, FALSE); // we shouldn't add 1 here if I'm correct
}

void	ft_lfork(t_env *e, t_process *cursor, t_op op)
{
	t_process	*child;

	child = new_process(cursor->player, cursor->alive, e->last_pid++);
	duplicate_process(child, cursor);
	child->pc = POSMOD(cursor->pc + cursor->args[0].value);
	VERB(VERB_OP, ft_printf(" (%d)", child->pc));
	push_process_front(&e->cursors, child);
	read_instruction(e, child, FALSE);
}

void	ft_add(t_env *e, t_process *cursor, t_op op)
{
	int		res;

	set_reg_values(cursor, op, 2);
	res = cursor->args[0].value + cursor->args[1].value;
	cursor->regs[cursor->args[2].value - 1] = res;
	cursor->carry = !res;
}

void	ft_sub(t_env *e, t_process *cursor, t_op op)
{
	int		res;

	set_reg_values(cursor, op, 2);
	res = cursor->args[0].value - cursor->args[1].value;
	cursor->regs[cursor->args[2].value - 1] = res;
	cursor->carry = !res;
}
void	ft_or(t_env *e, t_process *cursor, t_op op)
{
	int		res;

	set_reg_values(cursor, op, 2);
	charge_memory(e, cursor, op, TRUE); // NOIDEA
	res = cursor->args[0].value | cursor->args[1].value;
	cursor->regs[cursor->args[2].value - 1] = res;
	cursor->carry = !res;
}

void	ft_xor(t_env *e, t_process *cursor, t_op op)
{
	int		res;

	//DEBUG(d_display_argument(cursor, op))
	set_reg_values(cursor, op, 2);
	charge_memory(e, cursor, op, TRUE); // NOIDEA
	res = cursor->args[0].value ^ cursor->args[1].value;
	cursor->regs[cursor->args[2].value - 1] = res;
	cursor->carry = !res;
}

void	ft_ldi(t_env *e, t_process *cursor, t_op op)
{
	int		addr;

	set_reg_values(cursor, op, 2);
	charge_memory(e, cursor, op, TRUE); // NOIDEA
	addr = MODX(cursor->args[0].value + cursor->args[1].value);
	cursor->regs[cursor->args[2].value - 1] = mix_bytes(e, cursor, addr, 4);
}

// need to be checked
void	ft_lld(t_env *e, t_process *cursor, t_op op)
{
	set_reg_values(cursor, op, 1);
	charge_memory(e, cursor, op, FALSE); // NOIDEA
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
	charge_memory(e, cursor, op, FALSE); // NOIDEA
	addr = cursor->args[0].value + cursor->args[1].value;
	cursor->regs[cursor->args[2].value - 1] = mix_bytes(e, cursor, addr, 4);
}
void	ft_aff(t_env *e, t_process *cursor, t_op op)
{
	char		c;

	c = cursor->regs[cursor->args[0].value - 1] % 256;
	VERB(VERB_AFF, ft_printf("aff: %c\n", c));
}
