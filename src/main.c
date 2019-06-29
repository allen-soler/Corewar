/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/29 15:50:58 by jallen            #+#    #+#             */
/*   Updated: 2019/06/29 17:04:39 by jallen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

int main(int ac, char **av)
{
	char	*line;
	int		fd;
	t_par	*list;

	(void)ac;
	ft_printf("-here\n");
	list = ingest_file(av[1]);
	ft_printf("here\n");
	ft_printf("this %s\n", list->param);
	check_syntax(list);
	line = ft_strdup("");
	fd = open(av[1], O_RDONLY);
	ft_printf("%s\n", list->param);
	while (list)
	{
		ft_printf("%s\n", list->param);
		list = list->next;
	}
	readfile(fd, &line);
	close(fd);
	to_binary(line);
	free(line);
	return (0);
}
