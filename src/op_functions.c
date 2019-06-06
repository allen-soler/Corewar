#include "../includes/vm.h"

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

/*
**	Function: mix_bytes
**	Takes an index and the number of bytes you want to mix
**	and it'll mix those bytes into one number.
*/

int		mix_bytes(t_env *e, int index, int len)
{
	int	res;
	int	i;

	i = 0;
	res = 0;
	while (i < len)
	{
		res = (res << 8) | e->arena[index++].data;
		i += 1;
	}
	return (res);
}

/*
**	Function: read_args
**	This function will read the enconding byte if it exists and read
**	the associated arguments afterwards, it supposes the cursor->pc
**	is set to the instructions index.
**	This function should work with all the op's, those who have an
**	encoding byte and those who don't.
*/

void	read_args(t_env *e, t_process *cursor, t_op op)
{
	int			i;
	int			type;
	int			arg_len;
	int			offset;


	if (op.encoding_byte)
		offset = 2;
	else
		offset = 1;
	reset_args(cursor);
	i = 0;
	while (i < op.param_nb)
	{
		if (op.encoding_byte)
		{
			type = e->arena[cursor->pc + 1].data;
			if (type >> (i * 2) != 0)
			{
				/*
				** In this bitwise operation we are taking the byte that
				** represents the arguments and taking the last two bytes (& 3 should do the work),
				** after previously shifting to right in reversed order (type >> decresing_size).
				*/

				type = (type >> ((op.param_nb - i) * 2) & 3);
				cursor->args[i].type = type;
			
				/*
				** An argument can have a different size depending on both it's
				** type and the op_code.
				** For example a direct type (T_DIR) can have a size of 4 or 2 bytes,
				** while an indirect type (T_IND) will always have a size of 2 bytes
				** and a register (T_REG) will always have a size of 1 byte.
				*/

				arg_len = 1;
				if ((op.direct_size == 1 && type == T_DIR) || type == T_IND)
				{
					arg_len = 2;
				}
				else if (type == T_DIR && op.direct_size == 0)
				{
					arg_len = 4;
				}
			}
		}
		else
		{
			/*
			**	When an instruction doesn't have an encoding byte it'll always have one argument
			**	and it's always of type T_DIR
			*/

			cursor->args[i].type = T_DIR;
			arg_len = 4;
		}

		cursor->args[i].value = mix_bytes(e, cursor->pc + offset, arg_len);
		offset += arg_len;
		i += 1;
	}
}

void	ft_live(t_env *e, t_process *cursor, t_op op)
{
	int i;

	i = 0;
	read_args(e, cursor, op);
	d_display_argument(cursor, op);
	while (i < op_tab[0].param_nb)
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
