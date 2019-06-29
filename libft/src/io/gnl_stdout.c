/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_stdout.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalonso <nalonso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 16:42:04 by nalonso           #+#    #+#             */
/*   Updated: 2019/04/09 16:42:05 by nalonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl.h"

/*
** Function: gnl_stdout
** ---------------------
** simpler implementation of get_next_line, that reads the whole stdin and
** after that it returns up to a '\n' or '\0' and saves the rest.
**
** line: pointer where the line will be stored
*/

static char	*readfile(char *str, int fd)
{
	char		buff[BUFF_SIZE + 1];
	char		*ptr;
	int			ret;

	while ((ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		ptr = str;
		buff[ret] = '\0';
		str = ft_strjoin(str, buff);
		free(ptr);
	}
	return (str);
}

int			gnl_stdout(char **line)
{
	static char	*str;
	size_t		i;

	if (line == NULL || read(0, &i, 0) < 0 || BUFF_SIZE <= 0)
		return (-1);
	if (!str && !(str = malloc(sizeof(char) * (BUFF_SIZE + 1))))
		return (-1);
	str = readfile(str, 0);
	i = 0;
	if (str[i])
	{
		while (str[i] != '\n' && str[i])
			i++;
		if (i == 0)
			(*line) = ft_strdup("");
		else
		{
			*line = ft_strsub(str, 0, i);
			str += i + 1;
		}
		return (1);
	}
	return (0);
}
