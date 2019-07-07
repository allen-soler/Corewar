#include "vm.h"

static void (*g_func_ptr[17])(t_env *e, t_process *cursor, t_op op) =
{
	ft_live, ft_ld, ft_st, ft_add, ft_sub, ft_and, ft_or,
	ft_xor, ft_zjmp, ft_ldi, ft_sti, ft_fork, ft_lld, ft_lldi,
	ft_lfork, ft_aff
};

static void		init_loop(t_loop *loop, int player_nb)
{
	loop->nb_process_alive = 0;
	loop->current_cycle = 0;
	loop->i_cycle = 0;
	loop->cycle_last_check = 0;
	loop->i_check = 0;
	loop->cycle_to_die = CYCLE_TO_DIE;
}

static void		exec_cmd(t_env *e, t_process *cursor)
{
	char op_code;

	op_code = cursor->op_code;
	if (op_code <= REG_NUMBER && op_code > 0)
	{
		DEBUG(ft_fprintf(2, "Excuting instruction %s with op_code: %d\n", op_tab[op_code - 1].name, op_code))
		if (read_args(e, cursor, op_tab[cursor->op_code - 1]))
		{
			g_func_ptr[op_code - 1](e, cursor, op_tab[op_code - 1]);
			VERB(VERB_OP, ft_printf("\n"));
		}
		// i took out the increment from here because it's taken care off in read_args
	}
	cursor->op_code = -1;
}


void			read_instruction(t_env *e, t_process *cursor, t_bool move_pc)
{
	int op;

	op = e->arena[cursor->pc].data;
	if (op > 0 && op <= REG_NUMBER)
	{
		cursor->op_code = op;
		cursor->cycle = op_tab[op - 1].nb_cycle;
		ft_printf("Reading op %d (%d cycles), for pid %d, (%d pc)\n", cursor->op_code, cursor->cycle, cursor->pid, cursor->pc);
	}
	else
	{
		if (move_pc)
			cursor->pc = (cursor->pc + 1) % MEM_SIZE;
		cursor->cycle = -1;
	}
}


/*
**	3 cases:
**			-no op (cycle == -1):			just move forward in the arena
**			-op w/cycle > 0:				cycle--
**			-op w/cycle == 0:				exec cmd
*/

void		init_processes(t_env *env)
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
		read_instruction(env, tmp, TRUE);
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

static int		check_live(t_env *e, t_loop *l)
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
			VERB(VERB_PROCESS_CREATION_DEATH, ft_printf("\tProcess 0 died\n"));
			tmp = index;
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
	/*  not necessary i think
	int i = 0;
	while (i < e->players_nb)
	{

		e->players[i].alive = 0;
		i += 1;
	}
	*/
	return (alive);
}


static void		exec_process(t_env *env)
{
	t_process	*curr;

	curr = env->cursors;
	while (curr != NULL)
	{
		if (curr->cycle <= 0)
			read_instruction(env, curr, TRUE);
		if (curr->cycle > 0)
			--curr->cycle;
		if (curr->cycle == 0 && curr->op_code != -1)
			exec_cmd(env, curr);
		curr = curr->next;
	}
}

int				run_cycle(t_env *e, t_loop *l)
{
	int nbr_live;

	l->current_cycle += 1;
	VERB(VERB_SHOW_CYCLES, ft_printf("It is now cycle %lu\n", l->current_cycle));
	exec_process(e);
	if (l->current_cycle - l->cycle_last_check >= l->cycle_to_die)
	{
		l->cycle_last_check = l->current_cycle;
		l->i_check += 1;
		nbr_live = check_live(e, l);
		ft_printf("nbr_live: %d\n", nbr_live);
		if (nbr_live >= NBR_LIVE || l->i_check == MAX_CHECKS)
		{
			l->cycle_to_die -= CYCLE_DELTA;
			l->i_check = 0;
			VERB(VERB_SHOW_CYCLES, ft_printf("Cycle to die is now %d\n", l->cycle_to_die));
		}
	}
	if (e->cursors == NULL)
		return (0);
	return (1);
}


void			game_loop(t_env *e)
{
	t_loop		l;
	int			cycle;

	init_loop(&l, e->players_nb);
	DEBUG(d_display_full_process(*e))
	cycle = 0;
	while (run_cycle(e, &l) == 1)
	{
		cycle += 1;
		if ((e->flag & FLAG_DUMP) && (cycle == e->dump))
		{
			print_arena(e);
			return ;
		}
	}
	if (e->cursors == NULL)
		print_winner(e);
}
