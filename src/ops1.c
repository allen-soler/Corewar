#include "../includes/vm.h"

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
	write_byte(e, addr + 1, cursor->args[0].value, DIR_SIZE);
}

void	ft_st(t_env *e, t_process *cursor, t_op op)
{
	int		addr;

	if (cursor->args[1].type == T_IND)
	{
		addr = cursor->pc + MODX(cursor->args[1].value);
		write_byte(e, addr + 1, cursor->regs[cursor->args[0].value - 1], DIR_SIZE);

	}
	else if( cursor->args[1].type == T_REG)
	{
		cursor->regs[cursor->args[1].value - 1] = cursor->regs[cursor->args[0].value - 1];
	}
}

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

