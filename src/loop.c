#include "vm.h"

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
	t_process	*index;

	index = env->cursors;
	while (index != NULL)
	{
		if (index->cycle == -1)
			index->pc = (index->pc + 1) % MEM_SIZE;
		else if (index->cycle > 0)
			index->cycle--;
		else if (index->cycle == 0)
		{
			//exec cmd: TODO: create each cmd
			index->cycle = -1;
		}
		index = index->next;
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
	while (l.nb_process_alive)
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
