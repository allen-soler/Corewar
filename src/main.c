/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/29 15:50:58 by jallen            #+#    #+#             */
/*   Updated: 2019/07/01 15:55:47 by jallen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void	test(t_par *lst)
{
	t_par *tmp;

	tmp = lst;
	while (tmp)
	{
	ft_printf("%s %i\n", tmp->param, tmp->type);
		tmp = tmp->next;
	}
	ft_printf("-----------------------------------------------------\n");
}

void	free_list(t_par *list)
{
	if (list->next)
		free_list(list->next);
	if (list->param)
		free(list->param);
	free(list);
}

int		main(int ac, char **av)
{
	char		*line;
	int			fd;
	t_par		*list;
	header_t	header;
	(void)ac;

	list = NULL;
	fd = open(av[1], O_RDONLY);
	line = ft_strdup("");
	readfile(fd, &line);
	close(fd);
	ingest_file(&list, line);
	check_syntax(list);
	test(list);
	to_binary(list, line, &header);
	free_list(list);
	free(line);
	return (0);
}
