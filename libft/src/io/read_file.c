/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 15:44:18 by jallen            #+#    #+#             */
/*   Updated: 2019/07/10 00:47:14 by jallen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl.h"

void	readfile(int fd, char **line)
{
	int		ret;
	char	*tmp;
	char	buff[BUFF_SIZE + 1];

	while ((ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[ret] = '\0';
		tmp = *line;
		*line = ft_strjoin(*line, buff);
		free(tmp);
	}
}
