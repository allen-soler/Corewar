/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encoding_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 23:10:19 by jallen            #+#    #+#             */
/*   Updated: 2019/07/10 00:28:33 by jallen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

size_t	djb_hash(char *str)
{
	unsigned long	hash;
	int				c;

	hash = 5381;
	if (!str)
		return (0);
	while ((c = *str++))
		hash = ((hash << 5) + hash) + c;
	return (hash);
}

int		nb_op(char *src)
{
	int	i;

	i = 0;
	while (op_tab[i].name)
	{
		if (djb_hash(src) == djb_hash(op_tab[i].name))
			break ;
		i++;
	}
	return (i);
}

void	prog_size(int value, int size, header_t *h)
{
	int		len;
	int8_t	i;
	int8_t	tmp;

	i = 0;
	tmp = 0;
	len = 11;
	while (size > 0)
	{
		tmp = ZMASK((value >> i));
		h->comment[len] = tmp;
		len--;
		size--;
		i += 8;
	}
}

void	write_byte(t_inst *inst, int32_t value, int32_t size)
{
	int		len;
	int8_t	i;
	int8_t	tmp;

	i = 0;
	inst->size += size - 1;
	len = inst->size - 1;
	while (size > 0)
	{
		tmp = ZMASK((value >> i));
		inst->tab[len + 1] = tmp;
		len--;
		i += 8;
		size--;
	}
}

void	get_binary(t_par *lst, t_inst *inst, int nb, int size)
{
	t_par	*tmp;
	int		i;
	int		bin;

	i = 0;
	bin = 6;
	tmp = lst;
	while (i < nb)
	{
		if (tmp->type == 1)
			inst->tab[size] = 0b01 << bin | inst->tab[size];
		else if (tmp->type == 2 || tmp->type == 3 || tmp->type == 5
				|| tmp->type == 15)
			inst->tab[size] = 0b10 << bin | inst->tab[size];
		else if (tmp->type == 4 || tmp->type == 9)
			inst->tab[size] = 0b11 << bin | inst->tab[size];
		tmp = tmp->next;
		bin -= 2;
		i++;
	}
	inst->size += 1;
}
