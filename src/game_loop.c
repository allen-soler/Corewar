/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allespag <allespag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 15:25:50 by allespag          #+#    #+#             */
/*   Updated: 2019/07/12 15:29:34 by allespag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void (*g_func_ptr[17])(t_env *e, t_process *cursor, t_op op) =
{
	ft_live, ft_ld, ft_st, ft_add, ft_sub, ft_and, ft_or,
	ft_xor, ft_zjmp, ft_ldi, ft_sti, ft_fork, ft_lld, ft_lldi,
	ft_lfork, ft_aff
};

static void		exec_cmd(t_env *e, t_process *cursor)
{
	char		op_code;

	op_code = cursor->op_code;
	if (op_code <= REG_NUMBER && op_code > 0)
	{
		if (read_args(e, cursor, g_op_tab[cursor->op_code - 1]))
		{
			g_func_ptr[op_code - 1](e, cursor, g_op_tab[op_code - 1]);
			VERB(VERB_OP, ft_printf("\n"));
		}
		cursor->pc = POSMOD(cursor->pc + cursor->a_len);
	}
	cursor->op_code = -1;
}

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
	int			nbr_live;

	l->current_cycle += 1;
	VERB(VERB_SHOW_CYCLES, ft_printf("It is now cycle %lu\n",
				l->current_cycle));
	exec_process(e);
	if (l->current_cycle - l->cycle_last_check >= l->cycle_to_die)
	{
		l->cycle_last_check = l->current_cycle;
		l->i_check += 1;
		nbr_live = check_live(e);
		if (nbr_live >= NBR_LIVE || l->i_check == MAX_CHECKS)
		{
			l->cycle_to_die -= CYCLE_DELTA;
			l->i_check = 0;
			VERB(VERB_SHOW_CYCLES, ft_printf("Cycle to die is now %d\n",
						l->cycle_to_die));
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

	init_loop(&l);
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
