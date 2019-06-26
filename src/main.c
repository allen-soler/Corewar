#include "../includes/asm.h"

int main(int ac, char **av)
{
	char	*line;
	int		i;
	int		fd;

	i = 1;
	if (ac > 1)
	{
		while(i < ac)
		{
			line = ft_strdup("");
			fd= open(av[i], O_RDONLY);
			readfile(fd, &line);
			ft_printf("%s\n", line);
			free(line);
			close(fd);
			i++;
		}
	}
	return (0);
}
