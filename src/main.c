/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/29 15:50:58 by jallen            #+#    #+#             */
/*   Updated: 2019/06/29 15:51:11 by jallen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

int main(int ac, char **av)
{
	char	*line;
	int		fd;
	t_par	*list;

	(void)ac;
	list = ingest_file(av[1]);
	check_syntax(list);
	line = ft_strdup("");
	fd = open(av[1], O_RDONLY);
	readfile(fd, &line);
	close(fd);
	to_binary(line);
	free(line);
	return (0);
}
