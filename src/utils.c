/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allespag <allespag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 14:25:57 by allespag          #+#    #+#             */
/*   Updated: 2019/07/09 15:11:32 by allespag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int			set_error(t_env *env)
{
	env->flag |= FLAG_ERROR;
	return (-1);
}

static int			pre_check(char *line, t_env *env)
{
	if (((line[0] < '0' || line[0] > '9')
		&& ((line[0] != '-') && line[0] != '+')))
		return (set_error(env));
	return (0);
}

static int			post_check(char *line, long long res, int sign, t_env *env)
{
	if ((((line[0] == '+' || line[0] == '-') && !line[1]))
		|| res * sign > INT_MAX || res * sign < INT_MIN)
		return (set_error(env));
	return (0);
}

int					ft_atoi_pimp(char *line, t_env *env)
{
	int				i;
	int				sign;
	long long		res;

	i = 0;
	sign = 1;
	res = 0;
	if (pre_check(line, env) == -1)
		return (-1);
	if (line[i] == '-' || line[i] == '+')
	{
		sign = ((line[i] == '-') ? -1 : 1);
		if (sign == -1)
			return (set_error(env));
		i++;
	}
	while (line[i] >= '0' && line[i] <= '9')
	{
		res = (res * 10) + line[i] - '0';
		i++;
	}
	if ((line[i] || post_check(line, res, sign, env) == -1))
		return (set_error(env));
	return ((int)(res * sign));
}

int					ft_endswith(const char *str, const char *suffix)
{
	size_t			len_str;
	size_t			len_suffix;

	if (!str || !suffix)
		return (0);
	len_str = ft_strlen(str);
	len_suffix = ft_strlen(suffix);
	if (len_suffix > len_str)
		return (0);
	return (ft_strncmp(str + len_str - len_suffix, suffix, len_suffix) == 0);
}
