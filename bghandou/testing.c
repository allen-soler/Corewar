/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandou <bghandou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 03:11:41 by bghandou          #+#    #+#             */
/*   Updated: 2019/05/21 03:18:22 by bghandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

#include <stdio.h>
#include <fcntl.h>


int main(int ac, char **av)
{
	int		fd;
	int		fd_write;
	char	*line;
	char	proc[10];

	int		decal;

	fd = open(av[1], O_RDONLY);
	get_next_line(fd, &line);
	fd_write = 0;
	decal = 45;
	close(fd);
	ft_bzero(proc, 10);
	if (!ft_strcmp("value", line))
	{
		proc[0] = 0;
		proc[1] = 234;
		proc[2] = 131;
		proc[3] = 243;
		fd_write = open("yo.cor", O_CREAT | O_RDWR);
		write(fd_write, proc, 10);
		decal = lseek(fd_write, 120, SEEK_SET);
		close(fd_write);
	}
	dprintf(1, "number : %d and string : %s\n", decal, line);
}
