#include "../includes/vm.h"

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
			ft_printf("Player %d(%s) is alive\n",\
					e->players[i].number, e->players[i].header.prog_name);
			e->players[i].alive += 1;
			e->last_live = i;
			break ;
		}
		++i;
	}
	cursor->pc = (cursor->pc + get_args_len(cursor, op)) % MEM_SIZE;
}

void	ft_sti(t_env *e, t_process *cursor, t_op op)
{
	int	i;
	unsigned char	indirect;
	int				pointer;

	read_args(e, cursor, op);
	d_display_argument(cursor, op);
	pointer = 0;
	i = 0;
	indirect = 0;
	while (i < op.param_nb)
	{
		if (cursor->args[i].type == T_DIR) // TODO: handle indirect
		{
			pointer += cursor->args[i].value;
		}
		i += 1;
	}
	if (indirect)
	{
		pointer += cursor->pc;
	}
	ft_printf("charging at address %d the value %d\n", pointer, cursor->regs[cursor->args[0].value - 1]);
	e->arena[pointer].data = cursor->regs[cursor->args[0].value - 1];
}

void	ft_ld(t_env *e, t_process *cursor, t_op op)
{
	return ;
}

void	ft_st(t_env *e, t_process *cursor, t_op op)
{
	return ;
}

// no idea if it makes sense or not
void	ft_add(t_env *e, t_process *cursor, t_op op)
{
	int	res;

	read_args(e, cursor, op);
	d_display_argument(cursor, op);
	res = cursor->regs[cursor->args[0].value] + cursor->regs[cursor->args[1].value];
	cursor->regs[cursor->args[2].value] = res;
	cursor->carry = !res;
	cursor->pc = (cursor->pc + get_args_len(cursor, op)) % MEM_SIZE;
}

void	ft_sub(t_env *e, t_process *cursor, t_op op)
{
	int	res;

	read_args(e, cursor, op);
	d_display_argument(cursor, op);
	res = cursor->regs[cursor->args[0].value] - cursor->regs[cursor->args[1].value];
	cursor->regs[cursor->args[2].value] = res;
	cursor->carry = !res;
	cursor->pc = (cursor->pc + get_args_len(cursor, op)) % MEM_SIZE;
}


// TODO: Handle indirect in shift_args
void	ft_and(t_env *e, t_process *cursor, t_op op)
{
	int	res;
	int	len;	

	read_args(e, cursor, op);
	len = get_args_len(cursor, op);
		ft_printf("{g}len in ft_and == %d{R}\n", len);
	shift_args(cursor, 2);
		d_display_argument(cursor, op);
	res = cursor->args[0].value & cursor->args[1].value;
	cursor->regs[cursor->args[2].value] = res;
	cursor->carry = !res;
	cursor->pc = posmod(cursor->pc + len - 1, MEM_SIZE);
}

// TODO: Handle indirect in shift_args
void	ft_or(t_env *e, t_process *cursor, t_op op)
{
	int	res;
	int	len;	

	read_args(e, cursor, op);
	len = get_args_len(cursor, op);
		ft_printf("{g}len in ft_or == %d{R}\n", len);
	shift_args(cursor, 2);
		d_display_argument(cursor, op);
	res = cursor->args[0].value | cursor->args[1].value;
	cursor->regs[cursor->args[2].value] = res;
	cursor->carry = !res;
	cursor->pc = posmod(cursor->pc + len - 1, MEM_SIZE);
}

// TODO: Handle indirect in shift_args
void	ft_xor(t_env *e, t_process *cursor, t_op op)
{
	int	res;
	int	len;	

	read_args(e, cursor, op);
	len = get_args_len(cursor, op);
		ft_printf("{g}len in ft_xor == %d{R}\n", len);
	shift_args(cursor, 2);
		d_display_argument(cursor, op);
	res = cursor->args[0].value ^ cursor->args[1].value;
	cursor->regs[cursor->args[2].value] = res;
	cursor->carry = !res;
	cursor->pc = posmod(cursor->pc + len - 1, MEM_SIZE);
}

void	ft_zjmp(t_env *e, t_process *cursor, t_op op)
{
	read_args(e, cursor, op);
	if (cursor->carry)
		cursor->pc = posmod(cursor->pc + (cursor->args[0].value % IDX_MOD), MEM_SIZE);
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
