#include "vm.h"

static void	get_files(char **av, t_env *env)
{
	int		i;

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

static void set_dump(char **av, int ac, int index, t_env *env)
{
	if (ac == index)
		set_error_value(env, ERROR_SPE_DUMP);
	else
	{
		env->dump = ft_atoi_pimp(av[index], env);
		if (env->flag & FLAG_ERROR)
		{
			env->flag ^= 1;
			set_error_value(env, ERROR_SPE_DUMP);
		}
	}
}

static int	set_flag(char **av, int ac, t_env *env)
{
	int		i;

	i = 1;
	if (ac == 1 || !ft_strcmp(av[1], "--help") || !ft_strcmp(av[1], "-h"))
		env->flag |= FLAG_HELP;
	else
	{
		while (i < ac)
		{
			if ((!ft_strcmp(av[i], "-v") || !ft_strcmp(av[i], "--visual")) && ++i)
				env->flag |= FLAG_VISU;
			else if ((!ft_strcmp(av[i], "-d") || !ft_strcmp(av[i], "--dump") || !ft_strcmp(av[i], "-dump")) && ++i)
			{
				env->flag |= FLAG_DUMP;
				set_dump(av, ac, i, env);
				i++;
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
		// there is no turn specify
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

static int	choose_turn(int used, t_env *env)
{
	int		i;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		if (!(used & (1 << i)))
			return (i);
		else
			i++;
	}
	// already 4 players
	set_error_value(env, ERROR_CHAMPION);
	return (-1);
}

static void	set_players(char **av, int ac, int i, t_env *env)
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
			{
				// turn already set
				set_error_value(env, ERROR_SME_NUMB);
				return ;
			}
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
			{
				// turn already set
				set_error_value(env, ERROR_SME_NUMB);
				return ;
			}
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
		{
			// unknown argv
			set_error_value(env, ERROR_UNK_ARGV);
			return ;
		}
	}
}

static void	shift_players(t_env *env)
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

void	display_help(t_env *env)
{
	ft_printf("Usage: ./corewar [-d N | -v] [[-n N <champion.cor>] <...>]\n\n");
	ft_printf("options:\n");
	ft_printf("\t--help (-h)\t: Show this message\n");
	ft_printf("\t--dump N (-d N)\t: Dump memory after N cycles then exits\n");
	ft_printf("\t--visual (-v)\t: Ncurses (or whatever) output mode\n");
	exit_vm(env, (env->flag & FLAG_ERROR) ? EXIT_FAILURE : EXIT_SUCCESS);
}

//TODO: FLAG_VISU must be the only flag
void		parsing_args(char **av, int ac, t_env *env)
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
	get_files(av, env);
	shift_players(env);
}
