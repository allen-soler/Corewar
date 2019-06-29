/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandou <bghandou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 14:05:13 by bghandou          #+#    #+#             */
/*   Updated: 2019/03/13 17:32:06 by bghandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*check_no_nwl(char **extra, char *buf, int *flag)
{
	char	*prev;
	char	*stock;
	size_t	len1;
	char	*len2;

	prev = 0;
	stock = 0;
	len1 = ft_strlenchar(*extra, '\n');
	len2 = ft_strchr(*extra, '\n');
	if (len2)
	{
		prev = ft_strsub(*extra, 0, len1);
		ft_strcpy(*extra, len2 + 1);
		*flag = 1;
		return (prev);
	}
	else if (ft_strlen(buf) == 0 && (!ft_strchr(*extra, '\n')))
	{
		prev = ft_strsub(*extra, 0, ft_strlen(*extra));
		prev[ft_strlen(*extra)] = '\0';
		ft_bzero(*extra, ft_strlen(*extra));
		*flag = 1;
	}
	return (prev);
}

char	*stock_in_extra(char **extra, char *buf, int *flag)
{
	char	*prev;
	char	*stock;

	prev = 0;
	stock = 0;
	if (!*extra)
	{
		*extra = ft_strnew(BUFF_SIZE + 1);
		ft_strcpy(*extra, buf);
	}
	else
	{
		stock = ft_strjoin(*extra, buf);
		ft_strdel(extra);
		*extra = ft_strdup(stock);
		ft_strdel(&stock);
	}
	if (*extra)
		prev = check_no_nwl(extra, buf, flag);
	return (prev);
}

int		get_next_line(const int fd, char **line)
{
	int			ret;
	static char	*extra[5000];
	char		buf[BUFF_SIZE + 1];
	int			flag;
	int			count;

	ret = 0;
	flag = 0;
	count = 0;
	if (!line || fd < 0 || fd > 5000 || BUFF_SIZE <= 0)
	{
		return (-1);
	}
	while ((ret = read(fd, buf, BUFF_SIZE)) || ft_strlen(extra[fd]))
	{
		if (ret == -1)
			return (-1);
		buf[ret] = '\0';
		*line = stock_in_extra(&extra[fd], buf, &flag);
		if (ft_strchr(buf, '\n') || flag == 1)
			return (1);
	}
	if (extra[fd])
		ft_strdel(&extra[fd]);
	return (0);
}
