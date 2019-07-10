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
	int				size;
	int				i;

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

void	shift_args(t_env *env, t_process *cursor, int shift, t_bool ind_mod)
{
	int				i;

	i = 0;
	while (i < shift)
	{
		if (cursor->args[i].type & T_REG)
			cursor->args[i].value = cursor->regs[cursor->args[i].value - 1];
		else if (cursor->args[i].type & T_DIR)
			;
		else if ((cursor->args[i].type & T_IND) && ind_mod == TRUE)
			cursor->args[i].value = mix_bytes(env, cursor, MODX(cursor->args[i].value), DIR_SIZE);
		else if ((cursor->args[i].type & T_IND) && ind_mod == FALSE)
			cursor->args[i].value = mix_bytes(env, cursor, cursor->args[i].value, DIR_SIZE);
		else
			ft_printf("{r}There is a problem in shift_args ; REMOVE THIS LINE{R}\n");
		i++;
	}
}

void	reset_args(t_process *cursor)
{
	u_int8_t		i;

	i = 0;
	while (i < MAX_ARGS_NUMBER)
	{
		cursor->args[i].type = 0;
		cursor->args[i].value = 0;
		i += 1;
	}
	cursor->a_len = 0;
}

/*
 **	Function: mix_bytes
 **	Takes an index and the number of bytes you want to mix
 **	and it'll mix those bytes into one number.
 */

int		mix_bytes(t_env *e, t_process *cursor, int offset, int bytes)
{
	unsigned short	res;
	unsigned int	res2;

	if (bytes == 1)
		return ((char)(ZMASK(e->arena[POSMOD(cursor->pc + offset)].data)));
	if (bytes == 2)
		res = (ZMASK(e->arena[POSMOD(cursor->pc + offset)].data) << 8) |
				ZMASK(e->arena[POSMOD(cursor->pc + offset + 1)].data);
	else if (bytes == 4)
		res2 = (ZMASK(e->arena[POSMOD(cursor->pc + offset)].data) << 24) |
				(ZMASK(e->arena[POSMOD(cursor->pc + offset + 1)].data) << 16) |
				(ZMASK(e->arena[POSMOD(cursor->pc + offset + 2)].data) << 8) |
				ZMASK(e->arena[POSMOD(cursor->pc + offset + 3)].data);
	if (bytes == 2)
		return ((short)res);
	return ((int)res2);
}

/*
 **	Function: read_args
 **	This function will read the enconding byte if it exists and read
 **	the associated arguments afterwards, it supposes the cursor->pc
 **	is set to the instructions index.
 **	This function should work with all the op's, those who have an
 **	encoding byte and those who don't.
 */

char	*verb_string;

void	verb_print_arg(t_process *cursor, t_argument *args, int i, t_op op)
{
	if (args[i].type == T_REG)
		verb_string = ft_strjoin(verb_string, ft_cprintf(" r%d", args[i].value));
	else if (args[i].type == T_IND)
		verb_string = ft_strjoin(verb_string, ft_cprintf(" %d", args[i].value));
	else if (args[i].type == T_DIR)
		verb_string = ft_strjoin(verb_string, ft_cprintf(" %d", args[i].value));
}

int		read_type(t_env *e, t_process *cursor, t_op op, int i)
{
	int type;
	int arg_len;

	arg_len = 0;
	if (op.encoding_byte)
	{
		type = e->arena[(cursor->pc + 1) % MEM_SIZE].data;
		type = (type >> ((3 - i) * 2) & 3); // another solution for this 3?
		if (type == 0b11)
			type = T_IND;
		cursor->args[i].type = type;
		arg_len = 1;
		if ((op.direct_size == 1 && type == T_DIR) || type == T_IND)
			arg_len = IND_SIZE;
		else if (type == T_DIR && op.direct_size == 0)
			arg_len = DIR_SIZE;
	}
	else
	{
		cursor->args[i].type = T_DIR;
		arg_len = (op.direct_size == 1) ? 2 : DIR_SIZE;
	}
	return (arg_len);
}

int		read_args(t_env *e, t_process *cursor, t_op op)
{
	int				i;
	int				arg_len;

	VERB(VERB_OP, verb_string = ft_cprintf("P%5d | %s", cursor->pid, op.name));
	reset_args(cursor);
	cursor->a_len = 1 + op.encoding_byte;
	i = 0;
	while (i < op.param_nb)
	{
		arg_len = read_type(e, cursor, op, i);
		cursor->args[i].value = mix_bytes(e, cursor, cursor->a_len, arg_len);
		cursor->a_len += arg_len;
		if ((g_op_tab[op.op_code - 1].param_possible[i] & cursor->args[i].type) == 0 ||
		(cursor->args[i].type == T_REG && (cursor->args[i].value <= 0 || cursor->args[i].value > REG_NUMBER)))
		{
			cursor->pc = POSMOD(cursor->pc + cursor->a_len);
			return (0);
		}
		VERB(VERB_OP, verb_print_arg(cursor, cursor->args, i, op));
		i += 1;
	}
	VERB(VERB_OP, ft_printf("%s", verb_string));
	return (1);
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
	int				i;

	i = -1;
	while (++i < op.param_nb)
	{
		if (i == skip_index || cursor->args[i].type != T_REG)
			continue;
		cursor->args[i].value = cursor->regs[cursor->args[i].value - 1];
	}
}
