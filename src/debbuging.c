#include "vm.h"

void			d_display_process(t_env e, t_process *pro)
{
	int			i;

	i = 0;
	if (pro == NULL)
	{
		ft_printf("%s{c}Process:%s{R} (null)\n", S_BOLD, E_BOLD);
		return ;
	}
	ft_printf("%s{c}Process:%s{R} %p\n", S_BOLD, E_BOLD, pro);
	ft_printf("\t%sRegistries%s:\n", S_BOLD, E_BOLD);
	while (i < REG_NUMBER)
	{
		ft_printf("\t\t%d: %s%d\n", i, (i < 10) ? " " : "", pro->regs[i]);
		i++;
	}
	ft_printf("\t%sPC%s: %d\n", S_BOLD, E_BOLD, pro->pc);
	ft_printf("\t%sCarry%s: %d\n", S_BOLD, E_BOLD, pro->carry);
	ft_printf("\t%sAlive%s: %d\n", S_BOLD, E_BOLD, pro->alive);
	ft_printf("\t%sPlayer%s: %d, %s\n", S_BOLD, E_BOLD, pro->player, e.players[pro->player - 1].header.prog_name);
	ft_printf("\t%sColor%s: %d\n", S_BOLD, E_BOLD, pro->color);
	ft_printf("\t%sPID%s: %d\n", S_BOLD, E_BOLD, pro->pid);
	ft_printf("\t%sPrev%s: %p\n", S_BOLD, E_BOLD, pro->prev);
	ft_printf("\t%sNext%s: %p\n", S_BOLD, E_BOLD, pro->next);
}

void			d_display_full_process(t_env env)
{
	t_process	*tmp;

	tmp = env.cursors;
	while (tmp != NULL)
	{
		ft_printf("{m}---------------------------{R}\n");
		d_display_process(env, tmp);
		ft_printf("{m}---------------------------{R}\n");
		tmp = tmp->next;
	}
}

void			d_display_argument(t_process *cursor, t_op op)
{
	int	i;

	i = 0;
	ft_printf("{m}---------------------------{R}\n");
	ft_printf("{m}Printing arguments of %s{R}\n", op.name);
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
	ft_printf("%s{c}Players{R}%s:\n", S_BOLD, E_BOLD);
	while (i < env.players_nb)
	{
		ft_printf("\t%sPlayer n_%d%s (index: %d)\n", S_BOLD, env.players[i].number, E_BOLD, i);
		ft_printf("\t\t%s-Parse_index%s = %d\n", S_BOLD, E_BOLD, env.players[i].parse_index);
		ft_printf("\t\t%s-Alive%s = %d\n", S_BOLD, E_BOLD, env.players[i].alive);
		ft_printf("\t\t%s-File path%s = %s\n", S_BOLD, E_BOLD, env.players[i].file);
		ft_printf("\t\t%s-Player name%s = %s\n", S_BOLD, E_BOLD, env.players[i].header.prog_name);
		ft_printf("\t\t%s-Player comment%s = %s\n", S_BOLD, E_BOLD, env.players[i].header.comment);
		i++;
	}
}

void			d_display_env(t_env env)
{
	// to add:
	//		- display players
	//		- display arena
	//		- display file
	ft_printf("{m}--------------T_ENV-------------{R}\n");
	ft_printf("%s{c}Flag{R}%s:\n", S_BOLD, E_BOLD);
	ft_printf("\t\t%s-Error%s: ", S_BOLD, E_BOLD);
		(env.flag & FLAG_ERROR) ? ft_printf("{g}[OK]{R}\n") : ft_printf("{r}[KO]{R}\n");
	ft_printf("\t\t%s-Help%s:  ", S_BOLD, E_BOLD);
		(env.flag & FLAG_HELP) ? ft_printf("{g}[OK]{R}\n") : ft_printf("{r}[KO]{R}\n");
	ft_printf("\t\t%s-Verb %d%s:  ", S_BOLD, env.verb, E_BOLD);
		(env.flag & FLAG_VERB) ? ft_printf("{g}[OK]{R}\n") : ft_printf("{r}[KO]{R}\n");
	ft_printf("\t\t%s-Dump%s:  ", S_BOLD, E_BOLD);
		(env.flag & FLAG_DUMP) ? ft_printf("{g}[OK]{R}\n") : ft_printf("{r}[KO]{R}\n");
	ft_printf("\t\t%s-Dbug%s:  ", S_BOLD, E_BOLD);
		(env.flag & FLAG_DBUG) ? ft_printf("{g}[OK]{R}\n") : ft_printf("{r}[KO]{R}\n");
	d_display_players(env);
	ft_putchar('\n');

	ft_printf("{y}%splayers_nb%s = %d{R}\n", S_BOLD, E_BOLD, env.players_nb);
	ft_printf("{y}%sdump%s = %d{R}\n", S_BOLD, E_BOLD, env.dump);

	ft_printf("{m}----------END_OF_T_ENV----------{R}\n");
}
