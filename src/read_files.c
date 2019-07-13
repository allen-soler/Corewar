/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalonso <nalonso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 09:54:08 by nalonso           #+#    #+#             */
/*   Updated: 2019/07/13 10:08:34 by nalonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

static uint32_t	swapb(uint32_t val)
{
	return (((val >> 24) & 0xFF) |
		((val << 8) & 0x00FF0000) |
		((val >> 8) & 0xFF00) |
		((val << 24) & 0xFF000000));
}

static void		parse_file2(t_env *e, int fd, int c, uint32_t champ_size)
{
	char	buff[CHAMP_MAX_SIZE];
	int		i;
	int		position;

	e->players[c].header.prog_size = swapb(e->players[c].header.prog_size);
	e->players[c].header.magic = swapb(e->players[c].header.magic);
	if (e->players[c].header.magic != COREWAR_EXEC_MAGIC)
	{
		ft_fprintf(2, "Error: Couldn't recognise corewar exec magic\n");
		exit_vm(e, EXIT_FAILURE);
	}
	if (e->players[c].header.prog_size != champ_size)
	{
		ft_fprintf(2, "Error: Champion size doesn't match prog size\n");
		exit_vm(e, EXIT_FAILURE);
	}
	if (read(fd, buff, champ_size) == champ_size)
	{
		i = -1;
		position = c * (MEM_SIZE / e->players_nb);
		while (++i < (int32_t)champ_size)
			e->arena[POSMOD(position + i)].data = buff[i];
	}
	else
		exit_vm(e, EXIT_FAILURE);
}

static void		parse_file(t_env *e, int fd, int curr)
{
	size_t	full_size;
	size_t	read_size;

	if ((full_size = lseek(fd, 0, SEEK_END)) <= sizeof(t_header))
	{
		ft_fprintf(2, "Error: Too small/empty file %s.\n",\
			e->players[curr].file);
		exit_vm(e, EXIT_FAILURE);
	}
	if (full_size - sizeof(t_header) > CHAMP_MAX_SIZE)
	{
		ft_fprintf(2, "Error: Champion %s too big (%d bytes > %d bytes)\n",\
		e->players[curr].file, full_size - sizeof(t_header), CHAMP_MAX_SIZE);
		exit_vm(e, EXIT_FAILURE);
	}
	lseek(fd, 0, SEEK_SET);
	if ((read_size = read(fd, &e->players[curr].header, sizeof(t_header)))\
		!= sizeof(t_header))
	{
		ft_fprintf(2, \
		"Error: File %s, incorrect header size (%d bytes != %d bytes).\n",\
		read_size, sizeof(t_header));
		exit_vm(e, EXIT_FAILURE);
	}
	parse_file2(e, fd, curr, full_size - sizeof(t_header));
}

void			read_files(t_env *e)
{
	int	curr;
	int	fd;

	curr = 0;
	while (curr < e->players_nb)
	{
		if ((fd = open(e->players[curr].file, O_RDONLY)) == -1)
		{
			ft_fprintf(2, "Error: Couldn't read file %s.\n",\
			e->players[curr].file);
			exit_vm(e, EXIT_FAILURE);
		}
		parse_file(e, fd, curr);
		close(fd);
		curr += 1;
	}
}
