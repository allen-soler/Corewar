#include "../includes/vm.h"

static void			get_files(t_env *e, int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (i < ac)
	{
		if (ft_endswith(av[i], ".cor") == 1)
		{
			e->players[j].file = av[i]; // FIXME: allocate ?
			j += 1;
		}
		i += 1;
	}
	e->players[j].file = NULL;
}

static void set_dump(char **av, int ac, int index, t_env *env)
{
	if (ac == index)
	{
		env->flag |= FLAG_ERROR;
		return ;
	}
	env->dump = ft_atoi_pimp(av[index], env);
}

static int	set_flag(char **av, int ac, t_env *env)
{
	int		i;

	i = 1;
	if (ac == 1 || !ft_strcmp(av[1], "--help"))
		env->flag |= FLAG_HELP;
	else
	{
		while (i < ac)
		{
			if ((!ft_strcmp(av[i], "-v") || !ft_strcmp(av[i], "--visual")) && ++i)
				env->flag |= FLAG_VISU;
			else if ((!ft_strcmp(av[i], "-d") || !ft_strcmp(av[i], "-dump")) && ++i)	//should be --dump
			{
				env->flag |= FLAG_DUMP;
				set_dump(av, ac, i, env);	// good index here because of the ++i, we have to sorry nestorino
			}
			else
				break ;
		}
	}
	return (i);
}

static int	set_player_turn(char **av, int ac, int index, t_env *env)
{
	int		turn;

	if (ac == index)
	{
		env->flag |= FLAG_ERROR;
		return (-1);
	}
	turn = ft_atoi_pimp(av[index], env);
	if (turn < 1 || turn > 4)
	{
		env->flag |= FLAG_ERROR;
		return (-1);
	}
	return (turn);
}

static int	choose_turn(int used, t_env *env)
{
	int		i;

	i = 0;
	while (i < 4)
	{
		if (!(used & (1 << i)))
			return (i);
		else
			i++;
	}
	env->flag |= FLAG_ERROR;
	return (-1);
}

static void	set_players(char **av, int ac, int i, t_env *env)
{
	int			turn;
	int			used;
	int			tmp_parse_index;
	t_player	new;

	(void)new;
	used = 0;
	tmp_parse_index = 0;
	while (i < ac)
	{
		if (!ft_strcmp(av[i], "-n") && ++i)
		{
			turn = set_player_turn(av, ac, i, env);
			if (turn == -1 || used & (1 << turn))
				env->flag |= FLAG_ERROR;
			else											// what do we do here in case of error ?
			{
				env->players[turn - 1].parse_index = tmp_parse_index;
				used |= (1 << turn);
			}
			tmp_parse_index++;
			i++;		// ??
		}
		else
		{
			turn = choose_turn(used, env);
			if (turn == -1)
				env->flag |= FLAG_ERROR;
			else
			{
				env->players[turn].parse_index = tmp_parse_index;
				used |= (1 << turn);
			}
			tmp_parse_index++;
			i++;
		}
	}
}

void		parsing_args(char **av, int ac, t_env *env)
{
	int		i;

	i = set_flag(av, ac, env); // TODO: when help flag activated we have to exit the program and don't continue with the parsing.
	set_players(av, ac, i, env);
	get_files(env, ac, av);
}
