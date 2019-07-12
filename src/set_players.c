/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_players.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allespag <allespag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 16:23:51 by allespag          #+#    #+#             */
/*   Updated: 2019/07/12 16:09:50 by allespag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		set_players(char **av, int ac, int i, t_env *env)
{
	int			turn;
	int			used;

	used = 0;
	while (i < ac)
	{
		if (!ft_strcmp(av[i], "-n") && ++i)
		{
			turn = set_player_turn(av, ac, i, env);
			if (turn == -1 || used & (1 << turn))
				set_error_exit(env, ERROR_SME_NUMB);
			else
			{
				env->players[turn].parse_index = ++i;
				env->players[turn].alive = 0;
				env->players_nb++;
				used |= (1 << turn);
				i++;
			}
		}
		else if (ft_endswith(av[i], ".cor") == 1)
		{
			turn = choose_turn(used, env);
			if (turn == -1)
				set_error_exit(env, ERROR_SME_NUMB);
			else
			{
				env->players[turn].parse_index = i;
				env->players[turn].alive = 0;
				env->players_nb++;
				used |= (1 << turn);
			}
			i++;
		}
		else
			set_error_exit(env, ERROR_UNK_ARGV);
	}
}
