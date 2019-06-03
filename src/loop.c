#include "vm.h"

static void (*g_func_ptr[1])(t_env *e, t_process *cursor) =
{
	ft_live, ft_ld, ft_st, ft_add, ft_sub, ft_and, ft_or,
	ft_xor, ft_zjmp, ft_ldi, ft_sti, ft_fork, ft_lld, ft_lldi,
	ft_lfork, ft_aff
};

static void		exec_cmd(t_env *e, t_process *cursor)
{
	char op_code;

	//print_arena(e);
	op_code = e->arena[cursor->pc].data;
	//ft_fprintf(2, "player pc -> %d data at that index -> %d\n", cursor->pc, op_code);
	if (op_code <= REG_NUMBER && op_code > 0) // make sure that the op code is valid
	{
		//ft_fprintf(2, "executing instruction with op_code  -> %d\n", op_code);
		g_func_ptr[e->arena[cursor->pc].data - 1](e, cursor);
	}
}

static void		init_loop(t_loop *loop, int player_nb)
{
	loop->nb_process_alive = player_nb;
	loop->current_cycle = 0;
	loop->i_cycle = 0;
	loop->i_check = 0;
	loop->cycle_to_die = CYCLE_TO_DIE;
}

/*
**	3 cases:
**			-no op (cycle == -1)			just move forward in the arena
**			-op w/cycle > 0:				cycle--
**			-op w/cycle == 0:				exec cmd
*/

static void		exec_process(t_env *env)
{
	t_process	*curr;

	curr = env->cursors;
	while (curr != NULL)
	{
		if (curr->cycle == -1)
			curr->pc = (curr->pc + 1) % MEM_SIZE; // isn't this incorrect, it'll reset the pc multiple times
		else if (curr->cycle > 0)
			curr->cycle--;
		else if (curr->cycle == 0)
		{
			//exec cmd: TODO: create each cmd
			exec_cmd(env, curr);
			curr->cycle = -1;
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
			alive++;
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

	i = 0;
	while (i < env->players_nb)
	{
		append_process(&env->cursors, new_process(env->players[i].number));
		i++;
	}
}

void		game_loop(t_env *env)
{
	t_loop		l;

	init_processes(env);
	init_loop(&l, env->players_nb);
	d_display_full_process(*env);
	while (l.nb_process_alive > 0)
	{
		l.i_cycle = 0;
		while (l.i_cycle < l.cycle_to_die)
		{
			if ((env->flag & FLAG_DUMP) && l.current_cycle == env->dump)
			{
				print_arena(env);
				return ;
			}
			exec_process(env);
			l.i_cycle++;
			l.current_cycle++;
//			ft_printf("{c}cycle: %d{R}\n", l.current_cycle);
		}
		l.nb_process_alive = check_live(env);
		if (l.nb_process_alive >= NBR_LIVE || l.i_check == MAX_CHECKS)
		{
			l.i_check = 0;
			l.cycle_to_die -= CYCLE_DELTA;
		}
		else
			l.i_check++;
	}
}
