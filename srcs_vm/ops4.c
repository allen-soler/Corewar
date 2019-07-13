/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops4.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalonso <nalonso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 09:54:01 by nalonso           #+#    #+#             */
/*   Updated: 2019/07/13 09:54:02 by nalonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

void	ft_aff(t_env *e, t_process *cursor, t_op op)
{
	char		c;

	(void)op;
	(void)e;
	c = cursor->regs[cursor->args[0].value - 1] % 256;
	VERB(VERB_AFF, ft_printf("aff: %c\n", c));
}
