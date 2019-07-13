/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allespag <allespag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 11:07:02 by allespag          #+#    #+#             */
/*   Updated: 2019/07/12 15:14:33 by allespag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

int				main(int ac, char **av)
{
	t_env		env;

	g_debug = 0;
	init_env(&env);
	parsing_args(av, ac, &env);
	read_files(&env);
	init_processes(&env);
	if (env.verb >= VERB_WINNER)
		display_contestants(&env);
	game_loop(&env);
	return (0);
}
