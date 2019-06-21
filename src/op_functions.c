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
	cursor->pc += get_args_len(cursor, op);
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

void	ft_add(t_env *e, t_process *cursor, t_op op)
{
	return ;
}

void	ft_sub(t_env *e, t_process *cursor, t_op op)
{
	return ;
}

void	ft_and(t_env *e, t_process *cursor, t_op op)
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
