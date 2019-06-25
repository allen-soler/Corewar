#include "../includes/vm.h"

void	ft_live(t_env *e, t_process *cursor, t_op op)
{
	int i;

	i = 0;
	read_args(e, cursor, op);
	d_display_argument(cursor, op);
	while (i < e->players_nb)
	{
		if (e->players[i].number == cursor->args[0].value)
		{
			ft_printf("Player %d(%s) is alive\n",\
					e->players[i].number, e->players[i].header.prog_name);
			cursor->alive += 1;
			e->last_live = i;
			break ;
		}
		++i;
	}
	cursor->pc += get_args_len(cursor, op) + 1;
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
		if (cursor->args[i].type == T_DIR)
		{
			pointer += cursor->args[i].value;
		}
		i += 1;
	}
	if (indirect)
	{
		pointer += cursor->pc;
	}
	e->arena[pointer].data = cursor->regs[cursor->args[0].value - 1];
	ft_printf("augmenting the pointer in %d bytes\n", get_args_len(cursor, op)); 
	cursor->pc = (cursor->pc + get_args_len(cursor, op) + 1) % MEM_SIZE;
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

	read_args(e, cursor, op);
	i = 0;
	cursor->regs[cursor->args[2].value] = cursor->args[0].value & cursor->args[1].value;
	ft_printf("Register %d now has the value %d\n", cursor->args[2].value,\
			cursor->regs[cursor->args[2].value]);
	if (cursor->regs[cursor->args[2].value] == 0)
	{
		cursor->carry = 1;
	}
	else
		cursor->carry = 0;
	cursor->pc = (cursor->pc + get_args_len(cursor, op) + 1) % MEM_SIZE;
}

void	ft_ld(t_env *e, t_process *cursor, t_op op)
{
	return ;
}

void	ft_st(t_env *e, t_process *cursor, t_op op)
{
	return ;
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

void	ft_zjmp(t_env *e, t_process *cursor, t_op op)
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
