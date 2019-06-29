#include "vm.h"

static void (*g_func_ptr[17])(t_env *e, t_process *cursor, t_op op) =
{
	ft_live, ft_ld, ft_st, ft_add, ft_sub, ft_and, ft_or,
	ft_xor, ft_zjmp, ft_ldi, ft_sti, ft_fork, ft_lld, ft_lldi,
	ft_lfork, ft_aff
};

static void		exec_cmd(t_env *e, t_process *cursor)
{
	char op_code;

	op_code = e->arena[cursor->pc].data;
	if (op_code <= REG_NUMBER && op_code > 0)
	{
		DEBUG(ft_fprintf(2, "Excuting instruction %s with op_code: %d\n", op_tab[op_code - 1].name, op_code))
		g_func_ptr[op_code - 1](e, cursor, op_tab[op_code - 1]);
	}
}

static void		init_loop(t_loop *loop, int player_nb)
{
	loop->nb_process_alive = player_nb;
	loop->current_cycle = 1;
	loop->i_cycle = 0;
	loop->i_check = 1;
	loop->cycle_to_die = CYCLE_TO_DIE;
}

/*
**	3 cases:
**			-no op (cycle == -1):			just move forward in the arena
**			-op w/cycle > 0:				cycle--
**			-op w/cycle == 0:				exec cmd
*/

static void		exec_process(t_env *env)
{
	t_process	*curr;

	curr = env->cursors;
	while (curr != NULL)
	{
		if (curr->cycle == 0)
		{
			if (env->arena[curr->pc].data > 0 && env->arena[curr->pc].data < 17)
			{
				curr->cycle = op_tab[env->arena[curr->pc].data - 1].nb_cycle;
				DEBUG(ft_printf("{g}Adding %d cycles to procces %s{R}\n", curr->cycle, env->players[curr->player - 1].header.prog_name))
			}
			else
				curr->pc = (curr->pc + 1) % MEM_SIZE;
		}
		if (curr->cycle > 0)
			curr->cycle--;
		if (curr->cycle == 0)
		{
			exec_cmd(env, curr);
		}
		curr = curr->next;
	}
}

static int		check_live(t_env *env)
{
	int			alive;
	t_process	*index;
	t_process	*tmp;

	alive = 0;
	index = env->cursors;
	while (index != NULL)
	{
		if (index->alive == 0)
		{
			tmp = index;
			index = index->next;
			delete_process(&env->cursors, tmp);
		}
		else
		{
			alive += index->alive;
			index->alive = 0;
			if (index->player >= 0 && index->player <= env->players_nb)	//dunno if it's ok
				env->players[index->player - 1].alive = 0;
			index = index->next;
		}
	}
	return (alive);
}

/*
**	Maybe fill the list from last player to first
*/

static void		init_processes(t_env *env)
{
	int			i;
	t_process	*tmp;

	i = 0;
	while (i < env->players_nb)
	{
		tmp = new_process(env->players[i].number, 1);
		if (!tmp)
			exit_failure("Error: malloc failed in init_processes", env);
		tmp->pc = i * (MEM_SIZE / env->players_nb);
		append_process(&env->cursors, tmp);
		i++;
	}
}

static void		print_winner(t_env *env)
{
	
	if (env->last_live != -1)
		ft_printf("Player %d (%s) is the winner!\n", env->players[env->last_live].number, env->players[env->last_live].header.prog_name);
	else
		ft_printf("no winner? you lossers\n");
	DEBUG(d_display_env(*env))
	exit_vm(env, EXIT_SUCCESS);
}

// Do we have to reset lives of each players at the end of a cycle ?
void			game_loop(t_env *env)
{
	t_loop		l;

	init_processes(env);
	init_loop(&l, env->players_nb);
	DEBUG(d_display_full_process(*env))
	while (l.nb_process_alive > 0)
	{
		l.i_cycle = 0;
		while (l.i_cycle < l.cycle_to_die)
		{
			DEBUG(ft_printf("{c}Cycle: %d{R}\nCycle_To_Die: %d\n", l.i_cycle, l.cycle_to_die));
			if ((env->flag & FLAG_DUMP) && (l.current_cycle == env->dump))
			{
				if (l.nb_process_alive <= 0)
				{
					d_display_full_process(*env);
					print_winner(env);
				}
				else
					print_arena(env);
				return ;
			}
			exec_process(env);
			l.i_cycle++;
			l.current_cycle++;
			ft_printf("{y}Total cycle: %d{R}\n", l.current_cycle);
		}
		l.nb_process_alive = check_live(env);
		if (env->cursors == NULL)
			print_winner(env);
		else if (l.nb_process_alive >= NBR_LIVE || l.i_check == MAX_CHECKS)
		{
			l.i_check = 1;
			l.cycle_to_die -= CYCLE_DELTA;
		}
		else
			l.i_check++;
	}
}
