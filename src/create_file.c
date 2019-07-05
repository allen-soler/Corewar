/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readfile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 15:43:01 by jallen            #+#    #+#             */
/*   Updated: 2019/07/05 12:16:54 by jallen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"
# define  BUFF_SIZE 1000000

int	open_file(char	*src, int fd)
{
	char	**tab;
	char	*name;

	tab = ft_strsplit(src, '"');
	name = ft_strjoin(tab[1], ".cor");
	ft_free_tab(tab);
	fd = open(name, O_WRONLY | O_CREAT, 0644);
	free(name);
	return (fd);
}

void	name(int fd, uint32_t x, header_t *h, char *src)
{
	int				i;
	char			**tab;
	unsigned char	byte;

	i = 0;
	tab = ft_strsplit(src, '"');
	while (i < 4 + ft_strlen(tab[1]))
	{
		if (i < 4)
		{
			byte = x >> ((3 - i) * 8) & 0xff;
			h->prog_name[i] = byte;
		}
		else
			h->prog_name[i] = tab[1][i - 4];
		i++;
	}
	ft_free_tab(tab);
}

void	comment(int fd, header_t *h, char *src)
{
	char	**tab;
	int		i;

	i = 0;
	tab = ft_strsplit(src, '"');
	while (i < ft_strlen(tab[1]))
	{
		h->comment[i + 12] = tab[1][i];
		i++;
	}
	ft_free_tab(tab);
}

void	to_binary(t_par *lst, char *src, header_t *h)
{
	char		**tab;
	int			fd;
	t_inst		inst;

	fd = 0;
	tab = ft_strsplit(src, '\n');
	fd = open_file(&tab[0][5], fd);
	ft_bzero(h->prog_name, PROG_NAME_LENGTH + 1); 
	ft_bzero(h->comment, COMMENT_LENGTH + 1); 
	name(fd, COREWAR_EXEC_MAGIC, h, &tab[0][5]);
	comment(fd, h, &tab[1][8]);
	encoding(lst, fd, &inst);
	h->comment[11] = inst.size;
	ft_free_tab(tab);
	write(fd, h->prog_name, 128);
	write(fd, h->comment, 2048);
	write(fd, inst.tab, inst.size);
	close(fd);
}
