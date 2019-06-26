#include "../includes/asm.h"
# define  BUFF_SIZE 1000000


int	open_file(char	*src, int fd)
{
	char	**tab;
	char	**ptr;
	char	*name;

	tab = ft_strsplit(src, ' ');
	ptr = tab;
	tab = ft_strsplit(tab[1], '"');
	ft_free_tab(ptr);
	name = ft_strjoin(tab[0], ".cor");
	ft_free_tab(tab);
	fd = open(name, O_WRONLY | O_CREAT, 0644);
	free(name);
	return (fd);
}

void	readfile(int fd, char **line)
{
	int ret;
	char *tmp;
	char buff[BUFF_SIZE + 1];
	int cnt = 0;

	ret = 0;
	while ((ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[ret] = '\0';
		tmp = *line;
		*line = ft_strjoin(*line, buff);
		if (cnt == BUFF_SIZE)
			break ;
		cnt += ret;
		free(tmp);
	}
}

void	nb_base(int fd, uint32_t x)
{
	int	i;
	unsigned char byte;

	i = 0;
	while(i < 4)
	{
		byte = x >> ((3 - i) * 8) & 0xff;
		write(fd, &byte, sizeof(byte));
		i += 1;
	}
}

void	name(char *src, int bytes, int fd)
{
	char	**tab;	
	int		len;
	int		i;

	i = 0;
	tab = ft_strsplit(src, '\"');
	len = ft_strlen(tab[1]);
	if (bytes == 128)
		write(fd, tab[1], ft_strlen(tab[1]));
	else if (bytes == 2048)
	{
		while (i > 21)
		{
			write(fd, "", 1);
			i++;	
		}
	}
	bytes = bytes == 128 ? bytes - 4 - len : bytes - len - 12;
	while (i < bytes)
	{
		write(fd, "", 1);
		i++;
	}
	free(tab);
}

void	to_binary(char *src)
{
	char	**tab;
	int		fd;

	fd = 0;
	fd = open_file(src, fd);	
	nb_base(fd, COREWAR_EXEC_MAGIC);
	tab = ft_strsplit(src, '\n');
	name(&tab[0][5], 128, fd);
	name(&tab[1][8], 2048, fd);
	close(fd);
}
