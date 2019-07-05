/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/29 15:50:58 by jallen            #+#    #+#             */
/*   Updated: 2019/07/05 15:18:25 by jallen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void	order_list(t_par **lst)
{
	int		i;
	t_par	*tmp;

	tmp = *lst;
	i = 0;
	while (tmp)
	{
		tmp->pos = i;
		tmp = tmp->next;
		i++;
	}
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

	list = NULL;
	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		line = ft_strdup("");
		readfile(fd, &line);
		close(fd);
		ingest_file(&list, line);
		check_syntax(list);
		ft_printf("HERE\n");
		order_list(&list);
		//to_binary(list, line, &header, av[1]);
		//free_list(list);
		//free(line);
	}
	return (0);
}
