/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_automata.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandou <bghandou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 17:09:41 by bghandou          #+#    #+#             */
/*   Updated: 2019/06/04 19:27:55 by bghandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"


char	*token_automata(char *line)
{
	size_t		i;
	size_t		count;
	const char 	**instructions;

	instructions = {"ld", "st", "live", "add", "sub", "and", "or", "xor",\
	"zjmp", "ldi", "sti", "lld", "lldi", "lfork", "fork", "aff"};
	i = 0;
	count = 0;
	while (line[i++] != '\0')
	{
		line 
	}

}

void	ingest_file(char *file)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	line = NULL;
	while (get_next_line(fd, &line))
	{

		free(line);
	}
}

int		main(int ac, char **av)
{
	ingest_file(av[1]);
}
