/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_loop.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allespag <allespag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 15:18:30 by allespag          #+#    #+#             */
/*   Updated: 2019/07/12 15:29:35 by allespag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			init_loop(t_loop *loop, int player_nb)
{
	loop->nb_process_alive = 0;
	loop->current_cycle = 0;
	loop->i_cycle = 0;
	loop->cycle_last_check = 0;
	loop->i_check = 0;
	loop->cycle_to_die = CYCLE_TO_DIE;
}

void			init_processes(t_env *env)
{
	int			i;
	t_process	*tmp;

	i = 0;
	while (i < env->players_nb)
	{
		tmp = new_process(env->players[i].number, 1, env->last_pid);
		tmp->regs[0] = env->players[i].number;
		env->last_pid += 1;
		if (!tmp)
			exit_failure("Error: malloc failed in init_processes", env);
		tmp->pc = i * (MEM_SIZE / env->players_nb);
		read_instruction(env, tmp, TRUE);
		env->last_live = i;
		push_process_front(&env->cursors, tmp);
		i++;
	}
}

void			read_instruction(t_env *e, t_process *cursor, t_bool move_pc)
{
	int			op;

	op = e->arena[cursor->pc].data;
	if (op > 0 && op <= REG_NUMBER)
	{
		cursor->op_code = op;
		cursor->cycle = g_op_tab[op - 1].nb_cycle;
	}
	else
	{
		if (move_pc)
			cursor->pc = (cursor->pc + 1) % MEM_SIZE;
		cursor->cycle = -1;
	}
}
