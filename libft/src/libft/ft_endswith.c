/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_endswith.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalonso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 16:22:11 by nalonso           #+#    #+#             */
/*   Updated: 2019/05/31 16:22:15 by nalonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_endswith(const char *str, const char *suffix)
{
	size_t	len_str;
	size_t	len_suffix;

	if (!str || !suffix)
		return (0);
	len_str = ft_strlen(str);
	len_suffix = ft_strlen(suffix);
	if (len_suffix > len_str)
		return (0);
	return (ft_strncmp(str + len_str - len_suffix, suffix, len_suffix) == 0);
}
