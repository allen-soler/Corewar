#include "../includes/vm.h"

static void parse_file(t_env *env, int fd, int curr)
{
	ssize_t		size;
	char		instruction;
	off_t		offset;

	if ((size = read(fd, &(env->players[curr].header), sizeof(header_t))) != sizeof(header_t))
	{
		ft_fprintf(2, "Error: File %s header has an incorrect size (%d bytes != %d bytes).\n", size, sizeof(header_t));
		exit_vm(env, EXIT_FAILURE);
	}
	if ((offset = lseek(fd, 0,SEEK_END) - sizeof(header_t)) > CHAMP_MAX_SIZE)
	{
		ft_fprintf(2, "Error: File %s has too large of a code (%d bytes > %d bytes)\n",\
					env->players[curr].file, offset, CHAMP_MAX_SIZE);
		exit_vm(env, EXIT_FAILURE);
	}
}

void read_files(t_env *e)
{
	int curr;
	int fd;

	curr = 0;
	while (curr < MAX_PLAYERS)
	{
		if (e->players[curr].parse_index == -1)
		{
			curr += 1;
			continue ;
		}
		if ((fd = open(e->players[curr].file, O_RDONLY)) == -1)
		{
			ft_printf("error: %s\n", e->players[curr].file);
			exit_failure("ERROR: Couldn't open the file", e);
		}
		parse_file(e, fd, curr);
		close(fd);
		curr += 1;
	}
}
