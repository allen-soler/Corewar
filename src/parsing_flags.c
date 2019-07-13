/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_flags.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allespag <allespag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 13:26:58 by allespag          #+#    #+#             */
/*   Updated: 2019/07/12 15:04:52 by allespag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static t_bool	set_dump(char **av, int ac, int index, t_env *env)
{
	t_bool		is_good;

	is_good = FALSE;
	if (ac == index)
	{
		set_error_value(env, ERROR_SPE_DUMP);
		return (FALSE);
	}
	else
	{
		env->dump = ft_atoi_pimp(av[index], env);
		if (env->flag & FLAG_ERROR)
		{
			env->flag = 0;
			set_error_value(env, ERROR_SPE_DUMP);
		}
		else if (ac != index + 1)
		{
			env->n_dump = ft_atoi(av[index + 1]);
			is_good = (env->n_dump != 32 && env->n_dump != 64) ? FALSE : TRUE;
			env->n_dump = (env->n_dump != 64) ? 32 : 64;
			return (is_good);
		}
	}
	return (FALSE);
}

static int		exec_dump(char **av, int ac, int i, t_env *env)
{
	env->flag |= FLAG_DUMP;
	return (set_dump(av, ac, i, env) + 1);
}

static void		set_verb_level(char **av, int ac, int index, t_env *env)
{
	int			level;

	if (ac == index)
		set_error_value(env, ERROR_SPE_LEVL);
	else
	{
		level = ft_atoi_pimp(av[index], env);
		if ((env->flag & FLAG_ERROR) || level < 0 || level > 4)
		{
			env->flag = 0;
			set_error_value(env, ERROR_WRG_LEVL);
		}
		else
			env->verb = (level == 0) ? 0 : (1 << (level - 1));
	}
}

static int		exec_verbosity(char **av, int ac, int i, t_env *env)
{
	env->flag |= FLAG_VERB;
	set_verb_level(av, ac, i, env);
	return (1);
}

int				set_flag(char **av, int ac, t_env *env)
{
	int			i;

	i = 1;
	if (ac == 1 || !ft_strcmp(av[1], "--help") || !ft_strcmp(av[1], "-h"))
		env->flag |= FLAG_HELP;
	else
	{
		while (i < ac)
		{
			if ((!ft_strcmp(av[i], "-v") || !ft_strcmp(av[i], "--verbose"))
					&& ++i)
				i += exec_verbosity(av, ac, i, env);
			else if ((!ft_strcmp(av[i], "-d") || !ft_strcmp(av[i], "--dump")
						|| !ft_strcmp(av[i], "-dump")) && ++i)
				i += exec_dump(av, ac, i, env);
			else if ((!ft_strcmp(av[i], "-c") || !ft_strcmp(av[i], "--color"))
					&& ++i)
				env->flag |= FLAG_COLR;
			else
				break ;
		}
	}
	return (i);
}
