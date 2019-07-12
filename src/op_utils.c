#include "../includes/vm.h"

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
	while (size--)
	{
		uint16_t ptr = POSMOD(addr + (size - 1));
		e->arena[ptr].data = r[i];
		i += 1;
	}
}

