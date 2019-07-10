/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readfile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 15:43:01 by jallen            #+#    #+#             */
/*   Updated: 2019/07/10 01:56:46 by jallen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

static int	open_file(char *src, int fd)
{
	int		i;
	char	*name;

	i = 0;
	while (src[i] && src[i] != '.')
		i++;
	src[i] = '\0';
	name = ft_strjoin(src, ".cor");
	fd = open(name, O_WRONLY | O_CREAT, 0644);
	ft_printf("Writing output program to %s\n", name);
	free(name);
	return (fd);
}

static void	name(uint32_t x, t_header *h, char *dest)
{
	int				i;
	unsigned char	byte;

	i = 0;
	while (i < 4 + (int)ft_strlen(dest))
	{
		if (i < 4)
		{
			byte = x >> ((3 - i) * 8) & 0xff;
			h->prog_name[i] = byte;
		}
		else
			h->prog_name[i] = dest[i - 4];
		i++;
	}
	free(dest);
}

static void	comment(t_header *h, char *src)
{
	int		i;

	i = 0;
	while (i < (int)ft_strlen(src))
	{
		h->comment[i + 12] = src[i];
		i++;
	}
	free(src);
}

void		to_binary(t_par *lst, char *src, t_header *h, char *n_file)
{
	int			fd;
	t_inst		inst;

	fd = 0;
	fd = open_file(n_file, fd);
	ft_bzero(h->prog_name, PROG_NAME_LENGTH + 1);
	ft_bzero(h->comment, COMMENT_LENGTH + 17);
	name(COREWAR_EXEC_MAGIC, h, find_index(lst, src));
	comment(h, find_index(lst->next, src));
	encoding(lst, &inst);
	prog_size(inst.size, 4, h);
	write(fd, h->prog_name, 128);
	write(fd, h->comment, 2048 + 16);
	write(fd, inst.tab, inst.size);
	close(fd);
}
