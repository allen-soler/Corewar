/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalonso <nalonso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 16:51:43 by nalonso           #+#    #+#             */
/*   Updated: 2019/02/12 11:32:25 by nalonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int		word_count(char const *s, char c)
{
	int	len;

	len = 0;
	while (*s)
	{
		if (*s != c)
			len++;
		while (*s != c && *(s + 1))
			s++;
		s++;
	}
	return (len);
}

static int		word_length(char const *s, char c)
{
	int	len;

	len = 0;
	while (*s && *s == c)
		s++;
	while (*s++ != c && *s)
		len++;
	return (++len);
}

static char		*sp_strdup(char const *s, char c)
{
	char	*ret;
	char	*ptr;

	if (!(ret = (char *)malloc(sizeof(char) * (word_length(s, c) + 1))))
		return (NULL);
	ptr = ret;
	while (*s && *s != c)
		*ret++ = *s++;
	*ret = '\0';
	return (ptr);
}

static void		*free_tab(char **tab)
{
	while (*tab)
		free(*tab++);
	free(tab);
	return (NULL);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**tab;
	int		nb_word;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	nb_word = word_count(s, c);
	tab = (char **)malloc(sizeof(char *) * (nb_word + 1));
	if (!tab)
		return (NULL);
	while (i < nb_word)
	{
		while (*s && *s == c)
			s++;
		if (*s && !(tab[i] = sp_strdup(s, c)))
			return (free_tab(tab));
		while (*s != c && *s)
			s++;
		i++;
	}
	tab[nb_word] = NULL;
	return (tab);
}
