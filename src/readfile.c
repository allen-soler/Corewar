#include "../includes/asm.h"
# define  BUFF_SIZE 1000000

void readfile(int fd, char **line)
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
