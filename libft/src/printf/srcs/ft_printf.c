/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalonso <nalonso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 11:25:38 by nalonso           #+#    #+#             */
/*   Updated: 2019/01/14 15:41:13 by nalonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	ft_printf(const char *format, ...)
{
	va_list		arg;
	int			done;

	va_start(arg, format);
	done = handle_args(format, 1, arg);
	va_end(arg);
	return (done);
}

int	ft_fprintf(int fd, const char *format, ...)
{
	va_list		arg;
	int			done;

	va_start(arg, format);
	done = handle_args(format, fd, arg);
	va_end(arg);
	return (done);
}
