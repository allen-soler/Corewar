/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useful_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalonso <nalonso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 10:11:31 by nalonso           #+#    #+#             */
/*   Updated: 2019/01/21 12:43:42 by nalonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

char	*add_char(char *str, char c)
{
	char	*new;
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(str);
	new = (char *)malloc_safe(len + 2);
	new[0] = c;
	while (str[i] != '\0')
	{
		new[i + 1] = str[i];
		++i;
	}
	new[i + 1] = '\0';
	if (str)
		free(str);
	return (new);
}

char	*fstrjoin(char *s1, char *s2)
{
	char	*ptr;
	int		len1;
	int		len2;

	if (s1 && s2)
	{
		len1 = ft_strlen(s1);
		len2 = ft_strlen(s2);
		ptr = (char *)malloc_safe(len1 + len2 + 1);
		ft_strcpy(ptr, s1);
		ft_strcat(ptr, s2);
		free(s1);
		free(s2);
	}
	else
		return (NULL);
	return (ptr);
}

void	reverse(char str[], int length)
{
	int		start;
	int		end;
	char	tmp;

	start = 0;
	end = length - 1;
	while (start < end)
	{
		tmp = *(str + start);
		*(str + start) = *(str + end);
		*(str + end) = tmp;
		start++;
		end--;
	}
}

char	*ft_itoa_base(uintmax_t num, int base)
{
	char	str[128];
	int		i;
	int		rem;

	i = 0;
	if (num == 0)
		return (ft_strdup_safe("0"));
	while (num != 0)
	{
		rem = num % base;
		str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
		num = num / base;
	}
	str[i] = '\0';
	reverse(str, i);
	return (ft_strdup_safe(str));
}
