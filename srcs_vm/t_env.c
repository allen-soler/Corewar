/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalonso <nalonso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 14:11:59 by allespag          #+#    #+#             */
/*   Updated: 2019/07/13 12:23:19 by bghandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

void			set_error_value(t_env *env, t_error value)
{
	if (!(env->flag & FLAG_ERROR))
	{
		env->error_value = value;
		env->flag |= FLAG_ERROR;
	}
}

void			display_error(t_env *env)
{
	if (env->error_value > ERROR_MAX_VALUE)
		ft_fprintf(2, "{red}Error{eoc}\n\n");
	else
	{
		ft_fprintf(2, "{red}Error{eoc}: %s\n\n",
				env->error_str[env->error_value]);
	}
	display_help(env);
}

static void		init_arena(t_env *e)
{
	size_t		i;

	i = 0;
	while (i < MEM_SIZE)
	{
		e->arena[i].player = -1;
		e->arena[i].data = 0;
		i += 1;
	}
}

static void		init_env_error(t_env *env)
{
	env->error_str[0] = "Error, what are you trying to do ?";
	env->error_str[1] = "Need to specify number value after -n";
	env->error_str[2] = "Need to specify value after --dump (or value < 0)";
	env->error_str[3] = "You cannot use more than 4 champions";
	env->error_str[4] = "Cannot set 2 players with the same player number";
	env->error_str[5] = "Players number can only be from 1 to 4";
	env->error_str[6] = "Need to specify verbosity value after --verbose";
	env->error_str[7] = "Verbosity level can only be from 0 to 4";
	env->error_str[8] = "Unknown arguments";
}

void			init_env(t_env *env)
{
	int			i;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		env->players[i].parse_index = -1;
		env->players[i].file = NULL;
		i++;
	}
	env->players_nb = 0;
	env->flag = 0;
	env->last_live = -1;
	env->dump = -1;
	env->n_dump = 32;
	env->error_value = 0;
	env->last_pid = 0;
	env->verb = VERB_LIVE;
	init_arena(env);
	init_env_error(env);
	env->cursors = NULL;
}
