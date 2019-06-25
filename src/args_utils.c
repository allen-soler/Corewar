#include "../includes/vm.h"

/*
** @function: get_args_len
**
** @params	cursor: current process
**			op: info of current code
**
** @return total size of the arguments
**
*/ 

int		get_args_len(t_process *cursor, t_op op)
{
	int	size;
	int	i;

	i = 0;
	size = 0;
	while (i < op.param_nb)
	{
		if (cursor->args[i].type & T_REG)
			size += 1;
		else if (cursor->args[i].type & T_DIR)
			size += (op.direct_size == 1) ? 2 : DIR_SIZE;
		else if (cursor->args[i].type & T_IND)
			size += IND_SIZE;
		i += 1;
	}
	return (size + op.encoding_byte);
}

void	reset_args(t_process *cursor)
{
	u_int8_t	i;

	i = 0;
	while (i < MAX_ARGS_NUMBER)
	{
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
	unsigned int	res;
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
	e->arena[cursor->pc].player = 2;
	reset_args(cursor);
	i = 0;
	while (i < op.param_nb)
	{
		if (op.encoding_byte)
		{
			type = e->arena[(cursor->pc + 1) % MEM_SIZE].data;
			if (type >> (i * 2) != 0)
			{
				/*
				** In this bitwise operation we are taking the byte that
				** represents the arguments and taking the last two bytes (& 3 should do the work),
				** after previously shifting to right in reversed order (type >> decresing_size).
				*/

				type = (type >> ((3 - i) * 2) & 3); // that 3 is not the best solution
				if (type == 0b11)
					type = T_IND;
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
			arg_len = (op.direct_size == 1) ? 2 : DIR_SIZE;
		}
		cursor->args[i].value = mix_bytes(e, cursor->pc + offset, arg_len);
		offset += arg_len;
		i += 1;
	}
}

/*
** @function: set_reg_values
**
** @params: receives the cursor and the index (0-based) where it shouldn't do the change 
**
** This function will simply swap the register number @arg.value for the value
** stored in the register skipping the specified index
**
*/ 

void	set_reg_values(t_process *cursor, t_op op , int skip_index)
{
	int	i;

	i = -1;
	while (++i < op.param_nb)
	{
		if (i == skip_index || cursor->args[i].type != T_REG)
			continue;
		cursor->args[i].value = cursor->regs[cursor->args[i].value];
	}
}

