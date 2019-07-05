#include "vm.h"

void			d_display_process(t_env e, t_process *pro)
{
	int			i;

	i = 0;
	if (pro == NULL)
	{
		ft_printf("<bold>{CYN}Process:</bold><rst> (null)\n");
		return ;
	}
	ft_printf("<bold>{cyn}Process:</bold><rst> %p\n", pro);
	ft_printf("\t<bold>Registries</bold>:\n");
	while (i < REG_NUMBER)
	{
		ft_printf("\t\t%d: %s%d\n", i + 1, (i < 10) ? " " : "", pro->regs[i]);
		i++;
	}
	ft_printf("\t<bold>PC</bold>: %d\n", pro->pc);
	ft_printf("\t<bold>Carry</bold>: %d\n",pro->carry);
	ft_printf("\t<bold>Alive</bold>: %d\n", pro->alive);
	ft_printf("\t<bold>Player</bold>: %d, %s\n", pro->player, e.players[pro->player - 1].header.prog_name);
	ft_printf("\t<bold>Color</bold>: %d\n", pro->color);
	ft_printf("\t<bold>Op_Code</bold>: %d\n", pro->op_code);
	ft_printf("\t<bold>PID</bold>: %d\n", pro->pid);
	ft_printf("\t<bold>Prev</bold>: %p\n", pro->prev);
	ft_printf("\t<bold>Next</bold>: %p\n", pro->next);
}

void			d_display_full_process(t_env env)
{
	t_process	*tmp;

	tmp = env.cursors;
	while (tmp != NULL)
	{
		ft_printf("{PNK}---------------------------<rst>\n");
		d_display_process(env, tmp);
		ft_printf("{PNK}---------------------------<rst>\n");
		tmp = tmp->next;
	}
}

void			d_display_argument(t_process *cursor, t_op op)
{
	int	i;

	i = 0;
	ft_printf("{PNK}---------------------------<rst>\n");
	ft_printf("{PNK}Printing arguments of %s<rst>\n", op.name);
	while (i < MAX_ARGS_NUMBER)
	{
		if (cursor->args[i].type == T_REG)
			ft_printf("Arg %d of type T_REG (%b) with value: %d", i, cursor->args[i].type, cursor->args[i].value);
		else if (cursor->args[i].type == T_DIR)
			ft_printf("Arg %d of type T_DIR (%b) with value: %d", i, cursor->args[i].type, cursor->args[i].value);
		else if (cursor->args[i].type == T_IND)
			ft_printf("Arg %d of type T_IND (%b) with value: %d", i, cursor->args[i].type, cursor->args[i].value);
		else
			ft_printf("Arg %d of unknown type (%b) with value %d", i, cursor->args[i].type, cursor->args[i].value);
		ft_putendl(0);
		i += 1;
	}
	ft_printf("{m}---------------------------{R}\n");
}

void			d_display_players(t_env env)
{
	int			i;

	i = 0;
	ft_printf("<bold>{c}Players{R}</bold>:\n");
	while (i < env.players_nb)
	{
		ft_printf("\t<bold>Player n_%d</bold> (index: %d)\n", env.players[i].number, i);
		ft_printf("\t\t<bold>-Parse_index</bold> = %d\n", env.players[i].parse_index);
		ft_printf("\t\t<bold>-Alive</bold> = %d\n", env.players[i].alive);
		ft_printf("\t\t<bold>-File path</bold> = %s\n", env.players[i].file);
		ft_printf("\t\t<bold>-Player name</bold> = %s\n", env.players[i].header.prog_name);
		ft_printf("\t\t<bold>-Player comment</bold> = %s\n", env.players[i].header.comment);
		i++;
	}
}

void			d_display_env(t_env env)
{
	ft_printf("{PNK}--------------T_ENV-------------<rst>\n");
	ft_printf("<bold>{cyn}Flag<rst></bold>:\n");
	ft_printf("\t\t<bold>-Error</bold>: ");
		(env.flag & FLAG_ERROR) ? ft_printf("{GRN}[OK]<rst>\n") : ft_printf("{RED}[KO]<rst>\n");
	ft_printf("\t\t<bold>-Help</bold>:  ");
		(env.flag & FLAG_HELP) ? ft_printf("{GRN}[OK]<rst>\n") : ft_printf("{RED}[KO]<rst>\n");
	ft_printf("\t\t<bold>-Verb %d</bold>:  ", env.verb);
		(env.flag & FLAG_VERB) ? ft_printf("{GRN}[OK]<rst>\n") : ft_printf("{RED}[KO]<rst>\n");
	ft_printf("\t\t<bold>-Dump</bold>:  ");
		(env.flag & FLAG_DUMP) ? ft_printf("{GRN}[OK]<rst>\n") : ft_printf("{RED}[KO]<rst>\n");
	ft_printf("\t\t<bold>-Dbug</bold>:  ");
		(env.flag & FLAG_DBUG) ? ft_printf("{GRN}[OK]<rst>\n") : ft_printf("{RED}[KO]<rst>\n");
	d_display_players(env);
	ft_putchar('\n');

	ft_printf("{ylw}<bold>players_nb</bold> = %d<rst>\n", env.players_nb);
	ft_printf("{ylw}<bold>dump</bold> = %d<rst>\n", env.dump);

	ft_printf("{CYN}----------END_OF_T_ENV----------<rst>\n");
}
