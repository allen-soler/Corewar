/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 16:12:01 by jallen            #+#    #+#             */
/*   Updated: 2019/01/14 16:27:08 by jallen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	reset_buffer(t_printf *p)
{
	p->buff.current_index = 0;
	ft_memset(p->buff.str, '\0', PF_BUFF_SIZE);
}

void	write_buffer(t_printf *p)
{
	p->len += write(p->fd, p->buff.str, p->buff.current_index);
	reset_buffer(p);
}

void	buffer(t_printf *p, void *data, size_t size)
{
	int		diff;
	size_t	data_i;

	data_i = 0;
	if (!data)
		return ;
	while (PF_BUFF_SIZE - p->buff.current_index < size)
	{
		diff = PF_BUFF_SIZE - p->buff.current_index;
		ft_memcpy(&(p->buff.str[p->buff.current_index]), (data + data_i), diff);
		size -= diff;
		data_i += diff;
		p->buff.current_index += diff;
		write_buffer(p);
	}
	ft_memcpy(&(p->buff.str[p->buff.current_index]), (data + data_i), size);
	p->buff.current_index += size;
}
