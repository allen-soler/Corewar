#include "../includes/vm.h"

void	ft_live(t_env *e, t_process *cursor)
{
	int i;

	i = 0;
	ft_fprintf(2, "player %d says: living the good live out here ma'bois\n", cursor->player);
	while (i < op_tab[0].param_nb) // does this make sense?
	// isnt't live suppose to have just one parameter at the fourth byte?
	{
		return ;
	}
}

void	ft_ld(t_env *e, t_process *cursor)
{
	return ;
}

void	ft_st(t_env *e, t_process *cursor)
{
	return ;
}

void	ft_add(t_env *e, t_process *cursor)
{
	return ;
}

void	ft_sub(t_env *e, t_process *cursor)
{
	return ;
}

void	ft_and(t_env *e, t_process *cursor)
{
	return ;
}

void	ft_or(t_env *e, t_process *cursor)
{
	return ;
}

void	ft_xor(t_env *e, t_process *cursor)
{
	return ;
}

void	ft_zjmp(t_env *e, t_process *cursor)
{
	return ;
}

void	ft_ldi(t_env *e, t_process *cursor)
{
	return ;
}

void	ft_sti(t_env *e, t_process *cursor)
{

}

void	ft_fork(t_env *e, t_process *cursor)
{
	return ;
}

void	ft_lld(t_env *e, t_process *cursor)
{
	return ;
}

void	ft_lldi(t_env *e, t_process *cursor)
{
	return ;
}

void	ft_lfork(t_env *e, t_process *cursor)
{
	return ;
}

void	ft_aff(t_env *e, t_process *cursor)
{
	return ;
}
