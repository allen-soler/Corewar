/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_vm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allespag <allespag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 14:59:40 by allespag          #+#    #+#             */
/*   Updated: 2019/07/12 16:10:47 by allespag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

void	set_error_exit(t_env *e, t_error value)
{
	set_error_value(e, value);
	display_error(e);
	exit_vm(e, EXIT_FAILURE);
}

void	exit_vm(t_env *e, int status)
{
	exit(status);
}

void	exit_failure(const char *message, t_env *e)
{
	ft_fprintf(2, "%s\n", message);
	exit_vm(e, EXIT_FAILURE);
}
