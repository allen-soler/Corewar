/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allespag <allespag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 11:12:30 by allespag          #+#    #+#             */
/*   Updated: 2019/07/13 11:58:43 by allespag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

int				set_player_turn(char **av, int ac, int index, t_env *env)
{
	int			turn;

	if (ac == index)
	{
		set_error_value(env, ERROR_SPE_NUMB);
		return (-1);
	}
	turn = ft_atoi_pimp(av[index], env);
	if (turn < 1 || turn > 4)
	{
		set_error_value(env, ERROR_WRG_NUMB);
		return (-1);
	}
	return (turn - 1);
}

int				choose_turn(int used, t_env *env)
{
	int			i;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		if (!(used & (1 << i)))
			return (i);
		else
			i++;
	}
	set_error_value(env, ERROR_CHAMPION);
	return (-1);
}

static void		get_files(char **av, t_env *env)
{
	int			i;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		if (env->players[i].parse_index != -1)
		{
			env->players[i].file = av[env->players[i].parse_index];
			env->players[i].number = i + 1;
		}
		i++;
	}
}

static void		shift_players(t_env *env)
{
	int			i;
	int			j;

	i = 0;
	if (env->players_nb == MAX_PLAYERS)
		return ;
	while (i < MAX_PLAYERS)
	{
		if (env->players[i].parse_index == -1)
		{
			j = 0;
			while (i + j < MAX_PLAYERS)
			{
				if (env->players[i + j].parse_index != -1)
				{
					env->players[i] = env->players[i + j];
					env->players[i + j].parse_index = -1;
					break ;
				}
				j++;
			}
		}
		i++;
	}
}

void			parsing_args(char **av, int ac, t_env *env)
{
	int			i;

	i = set_flag(av, ac, env);
	if (env->flag & FLAG_ERROR)
		display_error(env);
	else if (env->flag & FLAG_HELP)
		display_help(env);
	set_players(av, ac, i, env);
	if (env->flag & FLAG_ERROR)
		display_error(env);
	if (env->players_nb == 0)
	{
		ft_fprintf(2, "{red}Error{eoc}: Need at least one champion\n\n");
		env->flag |= FLAG_ERROR;
		display_help(env);
	}
	get_files(av, env);
	shift_players(env);
}
