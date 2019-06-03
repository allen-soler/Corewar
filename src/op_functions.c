#include "../includes/vm.h"

void	ft_live(t_env *e, t_process *cursor, t_op op)
{
	int i;

	i = 0;
	ft_fprintf(2, "player %d says: living the good live out here ma'bois\n", cursor->player);
	while (i < op_tab[0].param_nb) // does this make sense?
	// isnt't live suppose to have just one parameter at the fourth byte?
	{
		return ;
	}
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

/*
**  Funtion: ft_sti
**
**	OP_CODE := 11
**	ARGUMENTS :=
*/

static int get_type(int byte)
{
	if (byte == T_REG)
		return (T_REG);
	else if (byte == T_DIR)
		return (T_DIR);
	else if (byte == T_IND)
		return (T_IND);
	return (0);
}

void	reset_args(t_process *cursor)
{
	u_int8_t	i;

	i = 0;
	while (i < MAX_ARGS_NUMBER)
	{
		cursor->args[i].type = 0;
		cursor->args[i].type = 0;
		i += 1;
	}
}

int		mix_bytes(t_env *e, int index, int len)
{
	int	res;
	int	i;

	i = 0;
	res = 0;
	while (i < len)
	{
		res = (res << 8) | e->arena[index++].data;
	}
	ft_printf("mixed %d bytes, having as a result: %d\n", len, res);
	return (res);
}

void	read_args(t_env *e, t_process *cursor, t_op op)
{
	u_int8_t	i;
	u_int8_t	type;

	reset_args(cursor);
	i = 0;
	while (i < op.param_nb)
	{
		type = e->arena[cursor->pc + 1].data;
		if (type >> (i * 2) != 0b0)
		{
			type = (type >> ((op.param_nb - i) * 2) & 3);
			cursor->args[i].type = type;
			cursor->args[i].value = e->arena[cursor->pc + i + 2].data;
		}
		i += 1;
	}
}

void	ft_sti(t_env *e, t_process *cursor, t_op op)
{
	int	i;
	unsigned char	indirect;
	int				pointer;
	read_args(e, cursor, op);
	d_display_argument(cursor);

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
