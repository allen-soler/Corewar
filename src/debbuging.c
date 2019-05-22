#include "../includes/vm.h"

void		d_display_players(t_env env)
{
	int		i;

	i = 0;
	ft_printf("%s{c}Players{R}%s:\n", S_BOLD, E_BOLD);
	while (i < MAX_PLAYERS)
	{
		if (env.players[i].parse_index != -1)
		{
			ft_printf("\t%sPlayer n_%d%s (i: %d)\n", S_BOLD, i + 1, E_BOLD, i);
			ft_printf("\t\t%s-Parse_index%s = %d\n", S_BOLD, E_BOLD, env.players[i].parse_index);
			ft_printf("\t\t%s-File path%s = %s\n", S_BOLD, E_BOLD, env.players[i].file);
			ft_printf("\t\t%s-Player name%s = %s\n", S_BOLD, E_BOLD, env.players[i].header.prog_name);
			ft_printf("\t\t%s-Player comment%s = %s\n", S_BOLD, E_BOLD, env.players[i].header.comment);
		}
		i++;
	}
}

void		d_display_env(t_env env)
{
	// to add:
	//		- display players
	//		- display arena
	//		- display file
	ft_printf("{m}----------T_ENV----------{R}\n");
	ft_printf("%s{c}Flag{R}%s:\n", S_BOLD, E_BOLD);
	ft_printf("\t\t%s-Error%s: ", S_BOLD, E_BOLD);
			(env.flag & FLAG_ERROR) ? ft_printf("{g}[OK]{R}\n") : ft_printf("{r}[KO]{R}\n");
	ft_printf("\t\t%s-Help%s:%s ", S_BOLD, E_BOLD);
			(env.flag & FLAG_HELP) ? ft_printf("{g}[OK]{R}\n") : ft_printf("{r}[KO]{R}\n");
	ft_printf("\t\t%s-Visu%s:%s ", S_BOLD, E_BOLD);
			(env.flag & FLAG_VISU) ? ft_printf("{g}[OK]{R}\n") : ft_printf("{r}[KO]{R}\n");
	ft_printf("\t\t%s-Dump%s:%s ", S_BOLD, E_BOLD);
			(env.flag & FLAG_DUMP) ? ft_printf("{g}[OK]{R}\n") : ft_printf("{r}[KO]{R}\n");

	d_display_players(env);

	ft_printf("\n{y}%sdump%s = %d{R}\n", S_BOLD, E_BOLD, env.dump);

	ft_printf("{m}----------END_OF_T_ENV----------{R}\n");
}
