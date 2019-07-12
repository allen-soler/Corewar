/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_stdin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalonso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 12:47:05 by nalonso           #+#    #+#             */
/*   Updated: 2019/04/09 11:30:01 by nalonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl.h"

int			ft_getc(int fd)
{
	char	buf;
	int		ret;

	if ((ret = read(fd, &buf, 1)))
		return (buf);
	return (_EOF);
}

static int	norme_getdelim(char **lineptr, size_t *n, int delim, int stream)
{
	char	*cur_pos;
	char	*new_lineptr;
	int		c;

	cur_pos = *lineptr;
	while (1)
	{
		if ((c = ft_getc(stream)) == -1 && cur_pos == *lineptr)
			return (-1);
		if (c == _EOF)
			break ;
		if ((*lineptr + *n - cur_pos) < 2)
		{
			if ((new_lineptr = (char *)ft_realloc(*lineptr, *n * 2, *n)))
				return (-1);
			cur_pos = new_lineptr + (cur_pos - *lineptr);
			*lineptr = new_lineptr;
			*n *= 2;
		}
		*cur_pos++ = (char)c;
		if (c == delim)
			break ;
	}
	*cur_pos = '\0';
	return (cur_pos - *lineptr);
}

int			ft_getdelim(char **lineptr, size_t *n, int delim, int stream)
{
	if (lineptr == NULL || n == NULL)
		return (-1);
	if (*lineptr == NULL)
	{
		*n = 128;
		if ((*lineptr = (char *)malloc(*n)) == NULL)
			return (-1);
	}
	return (norme_getdelim(lineptr, n, delim, stream));
}

int			ft_getline(char **lineptr, size_t *n, int stream)
{
	return (ft_getdelim(lineptr, n, '\n', stream));
}
