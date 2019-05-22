#include "../includes/vm.h"
#include "../includes/vm.h"

static void parse_file(t_player *curr, int fd)
{
	header_t header;

	read(fd, &(header), sizeof(header_t));
	ft_printf("%s - %s \n", header.prog_name, header.comment);
}

void read_files(t_env *e)
{
	int curr;
	int fd;

	curr = 0;
	while (curr < MAX_PLAYERS && curr)
	{
		if ((fd = open(e->players[curr].file, O_RDONLY)) == -1)
		{
			exit_failure("ERROR: Couldn't open the file", e);
		}
		parse_file(&e->players[curr], fd);
		close(fd);
		curr += 1;
	}
}
