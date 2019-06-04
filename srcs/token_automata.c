/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_automata.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandou <bghandou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 17:09:41 by bghandou          #+#    #+#             */
/*   Updated: 2019/06/04 17:23:37 by bghandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"


void	ingest_file(char *file)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	line = NULL;
	while (get_next_line(fd, &line))
	{
		ft_putstr(line);
		free(line);
	}
}

int		main(int ac, char **av)
{
	ingest_file(av[1]);
}
