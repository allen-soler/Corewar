/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/29 15:50:58 by jallen            #+#    #+#             */
/*   Updated: 2019/07/07 18:25:29 by jallen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

static size_t djb_hashh(const char* cp)
{
	size_t	hash;

	hash = 5381;
	while (*cp)
		hash = 33 * hash ^ (unsigned char)*cp++;
	return (hash);
}

int		nb_opp(char *src)
{
	int	i;

	i = 0;
	while (op_tab[i].name)
	{
		if (djb_hashh(src) == djb_hashh(op_tab[i].name))
			break ;
		i++;
	}
	return (i);
}

void	order_list(t_par **lst)
{
	int		i;
	t_par	*tmp;

	tmp = *lst;
	i = 0;
	while (tmp)
	{
		if (tmp->type == 7 || tmp->type == 6)
			break ;
		tmp = tmp->next;
	}
	int j = 0;
	int nb = 0;
	while (tmp)
	{
		if (tmp->type == 6)
			nb = nb_opp(tmp->param);
		if (tmp->type == 6)
			j = op_tab[nb].encoding_byte > 0 ? j + 2 : j + 1;
		else if (tmp->type == 1)
			j += 1;
		else if (tmp->type == 2 || tmp->type == 15 || tmp->type == 4 || tmp->type == 9)
				j += 2;
		else if (tmp->type == 3 || tmp->type == 5)
				j += 4;
		tmp->cnt = j;
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
		order_list(&list);
		to_binary(list, line, &header, av[1]);
		free_list(list);
		free(line);
	}
	return (0);
}
