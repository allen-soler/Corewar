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

	op_code = cursor->op_code;
	if (op_code <= REG_NUMBER && op_code > 0)
	{
		DEBUG(ft_fprintf(2, "Excuting instruction %s with op_code: %d\n", op_tab[op_code - 1].name, op_code))
		g_func_ptr[op_code - 1](e, cursor, op_tab[op_code - 1]);
		VERB(VERB_OP, ft_printf("\n"));
	}
	cursor->op_code = -1;
}


/*
**	3 cases:
**			-no op (cycle == -1):			just move forward in the arena
**			-op w/cycle > 0:				cycle--
**			-op w/cycle == 0:				exec cmd
*/
static int		check_live(t_env *e)
{
	int			alive;
	t_process	*index;
	t_process	*tmp;

	alive = 0;
	index = e->cursors;
	while (index != NULL)
	{
		if (index->alive == 0)
		{
			tmp = index;
			/* 
			VERB(VERB_PROCESS_CREATION_DEATH, ft_printf("\tProcess %d of player %d died\n",\
						index->pid - 1,
						index->player)); // should we add this to delete process?
						*/
			VERB(VERB_PROCESS_CREATION_DEATH, ft_printf("\tProcess 0 died\n"));
			index = index->next;
			delete_process(&e->cursors, tmp);
		}
		else
		{
			alive += index->alive;
			index->alive = 0;
			index = index->next;
		}
	}
	int i = 0;
	while (i < e->players_nb)
	{
		if (e->players[i].alive == 0 && e->players[i].death != 1)
		{
			e->players[i].death = 1;
		}
		else
		{
			e->players[i].alive = 0;
		}
		i += 1;
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
		tmp = new_process(env->players[i].number, 1, env->last_pid);
		env->last_pid += 1;
		if (!tmp)
			exit_failure("Error: malloc failed in init_processes", env);
		tmp->pc = i * (MEM_SIZE / env->players_nb);
		push_process_front(&env->cursors, tmp);
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

static void		exec_process(t_env *env)
{
	t_process	*curr;

	curr = env->cursors;
	while (curr != NULL)
	{
		if (curr->cycle <= 0)
		{
			if (env->arena[curr->pc].data > 0 && env->arena[curr->pc].data <= REG_NUMBER)
			{
				curr->op_code = env->arena[curr->pc].data;
				curr->cycle = op_tab[env->arena[curr->pc].data - 1].nb_cycle;
				DEBUG(ft_printf("{g}Adding %d cycles to procces %s pid(%d), for op %s{R}\n", curr->cycle, env->players[curr->player - 1].header.prog_name, curr->pid, op_tab[env->arena[curr->pc].data - 1].name))
			}
			else
				curr->pc = (curr->pc + 1) % MEM_SIZE;
		}
		if (curr->cycle > 0)
			curr->cycle--;
		if (curr->cycle == 0 && curr->op_code != -1)
			exec_cmd(env, curr);
		curr = curr->next;
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

int				run_cycle(t_env *e, t_loop *l)
{
	l->i_cycle = 0;
	while (l->i_cycle < l->cycle_to_die)
	{
		VERB(VERB_SHOW_CYCLES, ft_printf("It is now cycle %lu\n", l->current_cycle));
		exec_process(e);
		if ((e->flag & FLAG_DUMP) && (l->current_cycle == e->dump))
		{
			DEBUG(d_display_full_process(*e))
			print_arena(e);
			return (0);
		}
		++l->i_cycle;
		++l->current_cycle;
	}
	return (1);
}


void			game_loop(t_env *e)
{
	t_loop		l;

	init_processes(e);
	init_loop(&l, e->players_nb);
	DEBUG(d_display_full_process(*e))
	while (e->cursors != NULL)
	{
		if (!run_cycle(e, &l))
			break ;
		l.nb_process_alive = check_live(e);
		if (e->cursors == NULL)
			print_winner(e);
		else if (l.nb_process_alive >= NBR_LIVE || l.i_check == MAX_CHECKS)
		{
			l.i_check = 1;
			l.cycle_to_die -= CYCLE_DELTA;
			VERB(VERB_SHOW_CYCLES, ft_printf("Cycle to die is now %d\n", l.cycle_to_die));
		}
		else
			l.i_check++;
	}
}
