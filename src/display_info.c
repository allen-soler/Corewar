/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalonso <nalonso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 11:19:10 by allespag          #+#    #+#             */
/*   Updated: 2019/07/12 15:12:06 by allespag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		display_help(t_env *env)
{
	ft_printf("<bold>Usage: ./corewar [[-d N] -c] | -v N] "
			"[[-n N <champion.cor>] <...>]</bold>\n\n"
			"options:\n"
			"\t--help (-h)\t: Show this message\n"
			"\t--dump N (-d N)\t: Dump memory after N cycles then exits\n"
			"\t--color (-c)\t: Dump output with colors\n"
			"\t--verbose (-v)\t: Verbose mode (TODO: DISPLAY VERB LVL)\n"
			"\t\t0: winner (Player X (champion_name) won) "
			"and greetings message\n"
			"\t\t1: aff\n"
			"\t\t2: live (A process shows that player X "
			"(champion_name) is alive)"
			"{red} <- DEFAULT SETTING{eoc}\n"
			"\t\t3: process creation-death\n"
			"\t\t4: Show Cycles\n");
	exit_vm(env, (env->flag & FLAG_ERROR) ? EXIT_FAILURE : EXIT_SUCCESS);
}

void		display_contestants(t_env *env)
{
	int		i;

	i = 0;
	ft_printf("Introducing contestants...\n");
	while (i < env->players_nb)
	{
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
				env->players[i].number,
				env->players[i].header.prog_size,
				env->players[i].header.prog_name,
				env->players[i].header.comment);
		i++;
	}
}

void		print_arena(t_env *e)
{
	size_t	i;
	size_t	line;

	i = 0;
	line = 0;
	while (i < MEM_SIZE)
	{
		if (i % e->n_dump == 0)
		{
			ft_printf("0x%04x : ", line);
			line += e->n_dump;
		}
		if ((e->flag & FLAG_COLR) && e->arena[i].player == 0)
			ft_printf("{RED}%02hhx{eoc} ", e->arena[i++].data);
		else if ((e->flag & FLAG_COLR) && e->arena[i].player == 1)
			ft_printf("{CYN}%02hhx{eoc} ", e->arena[i++].data);
		else if ((e->flag & FLAG_COLR) && e->arena[i].player == 2)
			ft_printf("{GRN}%02hhx{eoc} ", e->arena[i++].data);
		else if ((e->flag & FLAG_COLR) && e->arena[i].player == 3)
			ft_printf("{YLW}%02hhx{eoc} ", e->arena[i++].data);
		else
			ft_printf("%02hhx ", e->arena[i++].data);
		if (i % e->n_dump == 0)
			ft_putchar('\n');
	}
}

void		print_winner(t_env *env)
{
	if (env->last_live != -1)
	{
		ft_printf("Player %d (%s) won \n",
				env->players[env->last_live].number,
				env->players[env->last_live].header.prog_name);
	}
	else
		ft_printf("no winner? you lossers\n");
}
