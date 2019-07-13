/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 09:36:57 by jallen            #+#    #+#             */
/*   Updated: 2019/07/13 10:44:59 by jallen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		is_blank(char c, char *split)
{
	int		i;

	i = 0;
	while (split[i])
	{
		if (c == split[i])
			return (1);
		i++;
	}
	return (0);
}

static size_t	count_words(char const *str, char *split)
{
	size_t	count;
	int		i;

	i = 0;
	count = 0;
	if (ft_strlen(str) == 0)
		return (0);
	while (str[i] != '\0')
	{
		if (!is_blank(str[i], split) && str[i] != '\0')
			count += 1;
		while (!is_blank(str[i], split) && str[i + 1] != '\0')
			i += 1;
		i += 1;
	}
	return (count);
}

static size_t	ft_wl(char const *str, char *split)
{
	size_t len;

	len = 0;
	while (!is_blank(str[len], split) && str[len] != '\0')
		len++;
	return (len);
}

char			**ft_split(char const *str, char *split)
{
	char	**tab;
	size_t	nb_words;
	size_t	i;

	i = 0;
	nb_words = count_words(str, split);
	if (!str || !(tab = (char **)malloc(sizeof(char *) * (nb_words + 1))))
		return (NULL);
	while (i < nb_words)
	{
		while (*str != '\0' && is_blank(*str, split))
			str++;
		tab[i] = ft_strndup(str, ft_wl(str, split));
		while (!is_blank(*str, split) && *(str) != '\0')
			str++;
		i++;
	}
	tab[nb_words] = NULL;
	return (tab);
}
