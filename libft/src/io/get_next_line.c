/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 13:57:24 by jallen            #+#    #+#             */
/*   Updated: 2019/06/27 15:46:16 by jallen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl.h"

t_list			*ft_get_file(t_list **file, int fd)
{
	t_list			*tmp;

	tmp = *file;
	while (tmp)
	{
		if ((int)tmp->content_size == fd)
			return (tmp);
		tmp = tmp->next;
	}
	tmp = ft_lstnew("\0", fd);
	ft_lstadd(file, tmp);
	tmp = *file;
	return (tmp);
}

char			*ft_vef_line(char *tmp, char **line)
{
	char			*ptr;
	char			*index;

	ptr = tmp;
	index = ft_strchr(tmp, '\n');
	if (index == 0)
	{
		*line = ft_strdup(tmp);
		free(ptr);
		tmp = ft_strdup("");
		return (tmp);
	}
	if (!(*line = ft_strsub(tmp, 0, index - tmp)))
		return (NULL);
	tmp = ft_strdup(index + 1);
	free(ptr);
	return (tmp);
}

int				get_next_line(const int fd, char **line)
{
	char			buf[BUFF_SIZE + 1];
	int				ret;
	static t_list	*file;
	t_list			*tmp;
	char			*ptr;

	if (fd < 0 || line == NULL || read(fd, buf, 0) < 0 || BUFF_SIZE <= 0)
		return (-1);
	tmp = ft_get_file(&file, fd);
	while ((ret = read(fd, buf, BUFF_SIZE)))
	{
		ptr = tmp->content;
		buf[ret] = '\0';
		tmp->content = ft_strjoin(tmp->content, buf);
		free(ptr);
		if (ft_strchr(tmp->content, '\n') != NULL)
			break ;
	}
	if (ret < BUFF_SIZE && !ft_strlen(tmp->content))
		return (0);
	tmp->content = ft_vef_line(tmp->content, line);
	return (1);
}
