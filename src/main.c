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

int		to_bin(char	*bin)
{
	char	*start = &bin[0];
	int		res;

	res = 0;
	while (*start)
	{
		res *= 2;
		if (*start++ == '1')
			res += 1;
	}
	return (res);
}

void	encoding(t_par *lst)
{
	int	i;

	i = 0;
	while (op_tab[i])
	{
		ft_printf("%s\n", op_tab[i]);
		i++;
	}
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
	//check_syntax(list);
	encoding(list);
	to_binary(list, line, &header);
	free(line);
	return (0);
}
