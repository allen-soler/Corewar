/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/29 15:50:58 by jallen            #+#    #+#             */
/*   Updated: 2019/07/13 11:54:22 by jallen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

static void	exit_msg(void)
{
	ft_fprintf(2, "Wrong file descriptor\n");
	exit(1);
}

static void	order_list(t_par **lst)
{
	int		i;
	int		j;
	t_par	*tmp;

	i = 0;
	j = 0;
	tmp = *lst;
	while (tmp)
	{
		if (tmp->type == 6 && i++)
			j = g_op_tab[nb_op(tmp->param)].encoding_byte > 0 ? j + 2 : j + 1;
		else if (tmp->type == 1 && i++)
			j += 1;
		else if ((tmp->type == 2 || tmp->type == 15 || tmp->type == 4
					|| tmp->type == 9) && i++)
			j += 2;
		else if ((tmp->type == 3 || tmp->type == 5) && i++)
			j += 4;
		tmp->cnt = j;
		if (tmp->type != 0)
			tmp->pos = i;
		tmp = tmp->next;
	}
}

static void	free_list(t_par *list)
{
	if (list)
	{
		if (list->next)
			free_list(list->next);
		if (list->param)
			free(list->param);
		free(list);
	}
}

static void	check_file(char *src)
{
	int	len;

	len = ft_strlen(src);
	if (len <= 2 || (src[len - 1] != 's' && src[len - 2] != '.'))
	{
		error_custom("Choose one valid '.s' file to compile.\n", NULL);
		exit(1);
	}
}

int			main(int ac, char **av)
{
	char		*line;
	int			fd;
	t_par		*list;
	t_header	header;

	list = NULL;
	if (ac == 2)
	{
		check_file(av[1]);
		if ((fd = open(av[1], O_RDONLY)) == -1)
			exit_msg();
		line = ft_strdup("");
		readfile(fd, &line);
		close(fd);
		list = ingest_file(av[1], 1);
		check_syntax(list);
		order_list(&list);
		to_binary(list, line, &header, av[1]);
		free_list(list);
		free(line);
	}
	else
		error_custom("Choose one valid '.s' file to compile.\n", NULL);
	return (0);
}
