/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readfile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 15:43:01 by jallen            #+#    #+#             */
/*   Updated: 2019/06/27 15:51:55 by jallen           ###   ########.fr       */
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

void	name(int fd, uint32_t x, char *name, char *src)
{
	int				i;
	char			**tab;
	unsigned char	byte;

	i = 0;
	tab = ft_strsplit(src, '"');
	name[PROG_NAME_LENGTH + 1] = '\0';
	while (i < 4 + ft_strlen(tab[1]))
	{
		if (i < 4)
		{
			byte = x >> ((3 - i) * 8) & 0xff;
			name[i] = byte;
		}
		else
			name[i] = tab[1][i - 4];
		i++;
	}
	write(fd, name, 128);
	ft_free_tab(tab);
}

void	comment(int fd, char *comment, char *src)
{
	char	**tab;
	int		i;

	i = 0;
	tab = ft_strsplit(src, '"');
	comment[COMMENT_LENGTH + 1] = '\0';
	while (i < ft_strlen(tab[1]))
	{
		comment[i + 12] = tab[1][i];
		i++;
	}
	write(fd, comment, 2048);
	ft_free_tab(tab);
}

void	to_binary(char *src)
{
	char		**tab;
	int			fd;
	header_t	header;

	fd = 0;
	tab = ft_strsplit(src, '\n');
	fd = open_file(&tab[0][5], fd);
	ft_bzero(header.prog_name, PROG_NAME_LENGTH + 1); 
	ft_bzero(header.comment, COMMENT_LENGTH + 1); 
	name(fd, COREWAR_EXEC_MAGIC, header.prog_name, &tab[0][5]);
	comment(fd, header.comment, &tab[1][8]);
	ft_free_tab(tab);
	close(fd);
}
