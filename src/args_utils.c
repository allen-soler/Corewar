#include "../includes/vm.h"

static void	reset_args(t_process *cursor)
{
	uint8_t		i;

	i = 0;
	while (i < MAX_ARGS_NUMBER)
	{
		cursor->args[i].type = 0;
		cursor->args[i].value = 0;
		i += 1;
	}
	cursor->a_len = 0;
}

int			read_type(t_env *e, t_process *cursor, t_op op, int i)
{
	uint8_t type;
	int arg_len;

	arg_len = 0;
	if (op.encoding_byte)
	{
		type = e->arena[(cursor->pc + 1) % MEM_SIZE].data;
		type = (type >> ((3 - i) * 2) & 0b11);
		if (type == 0)
			return (-1);
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

static t_bool	read_params(t_env *e, t_process *cursor, t_op op)
{
	int				i;
	int				arg_len;
	t_bool			fail;

	i = 0;
	fail = FALSE;
	while (i < op.param_nb)
	{
		if ((arg_len = read_type(e, cursor, op, i)) < 0)
		{
			fail = TRUE;
			i += 1;
			continue;
		}
		cursor->args[i].value = mix_bytes(e, cursor, cursor->a_len, arg_len);
		if ((g_op_tab[op.op_code - 1].param_possible[i] \
			& cursor->args[i].type) == 0 || (cursor->args[i].type == T_REG && \
			(cursor->args[i].value <= 0 || cursor->args[i].value > REG_NUMBER)))
			fail = TRUE;
		cursor->a_len += arg_len;
		i += 1;
	}
	return (fail);
}

int			read_args(t_env *e, t_process *cursor, t_op op)
{
	t_bool			fail;

	fail = FALSE;
	reset_args(cursor);
	cursor->a_len = 1 + op.encoding_byte;
	fail = read_params(e, cursor, op);
	return (fail == FALSE);
}
