/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/29 15:50:58 by jallen            #+#    #+#             */
/*   Updated: 2019/06/29 17:30:16 by jallen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

int main(int ac, char **av)
{
	char	*line;
	int		fd;
	t_par	*list;

	(void)ac;
	list = NULL;
	fd = open(av[1], O_RDONLY);
	line = ft_strdup("");
	readfile(fd, &line);
	close(fd);
	ingest_file(line, &list);
	while(list)
	{
		ft_printf("%s\n", list->param);
		list = list->next;
	}
	to_binary(line);
	free(line);
	return (0);
}
