#include "../includes/vm.h"

static void parse_file(t_env *env, int fd, int curr)
{
	ssize_t		size;
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
	if (lseek(fd, sizeof(header_t), SEEK_SET) == sizeof(header_t))
	{
		size = read(fd, &(env->arena[curr * (MEM_SIZE / env->players_nb)]), offset);
	}
}

void read_files(t_env *e)
{
	int curr;
	int fd;

	curr = 0;
	int i = 0;
	while (i < MEM_SIZE)
	{
		e->arena[i++] = 0;
	}
	while (curr < e->players_nb)
	{
		if ((fd = open(e->players[curr].file, O_RDONLY)) == -1)
		{
			ft_printf("error: %s\n", e->players[curr].file);
			exit_failure("ERROR: Couldn't open the file", e);
		}
		parse_file(e, fd, curr);
		close(fd);
		curr += 1;
	}

	i = 0;
	while (i < MEM_SIZE)
	{
		ft_printf("%02hhx ", e->arena[i++]);
		if (i % 64 == 0)
			ft_putendl(0);
	}
}
