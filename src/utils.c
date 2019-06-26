#include "vm.h"

int	posmod(int n, int mod)
{
	int	res;

	res = n % mod;
	if (res < 0 && mod > 0)
		res += mod;
	return (res);
}

int					ft_atoi_pimp(char *line, t_env *env)
{
	int				i;
	int				sign;
	long long		res;

	i = 0;
	sign = 1;
	res = 0;
	if (((line[i] < '0' || line[i] > '9')
		&& ((line[i] != '-') && line[i] != '+'))
		&& ft_strlen(line) < 12)
	{
		env->flag |= FLAG_ERROR;
		return (-1);
	}
	if (line[i] == '-' || line[i] == '+')
	{
		sign = ((line[i] == '-') ? -1 : 1);
		if (sign == -1)
		{
			env->flag |= FLAG_ERROR;
			return (-1);
		}
		i++;
	}
	while (line[i] >= '0' && line[i] <= '9')
	{
		res = (res * 10) + line[i] - '0';
		i++;
	}
	if (line[i] || (((line[0] == '+' || line[0] == '-') && !line[1]))
		|| res * sign > INT_MAX || res * sign < INT_MIN)
	{
		env->flag |= FLAG_ERROR;
		return (-1);
	}
	return ((int)(res * sign));
}
