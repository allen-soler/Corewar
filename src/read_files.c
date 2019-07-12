#include "../includes/vm.h"

uint32_t	swap32_bytes(uint32_t val)
{
	return (
		((val >> 24) & 0xFF) |
		((val << 8) & 0x00FF0000) |
		((val >> 8) & 0xFF00) |
		((val << 24) & 0xFF000000)
	);
}

static void parse_file(t_env *e, int fd, int curr)
{
	size_t full_size;
	size_t champ_size;
	size_t read_size;

	if (fd == -1)
		exit_vm(e, EXIT_FAILURE); // ejejej
	if ((full_size = lseek(fd, 0, SEEK_END)) <= sizeof(header_t))
	{
		ft_fprintf(2, "Error: Too small/empty file %s.\n",\
			e->players[curr].file);
		exit_vm(e, EXIT_FAILURE);
	}
	champ_size = full_size - sizeof(header_t);
	if (champ_size > CHAMP_MAX_SIZE)
	{
		ft_fprintf(2, "Error: File %s has too large of a code (%d bytes > %d bytes)\n",\
					e->players[curr].file, champ_size, CHAMP_MAX_SIZE);
		exit_vm(e, EXIT_FAILURE);
	}
	lseek(fd, 0, SEEK_SET); // after checking return to start
	if ((read_size = read(fd, &e->players[curr].header, sizeof(header_t))) != sizeof(header_t))
	{
		ft_fprintf(2, "Error: File %s header has an incorrect size (%d bytes != %d bytes).\n", read_size, sizeof(header_t));
		exit_vm(e, EXIT_FAILURE);
	}
	e->players[curr].header.prog_size = swap32_bytes(e->players[curr].header.prog_size);
	e->players[curr].header.magic = swap32_bytes(e->players[curr].header.magic);
	if (e->players[curr].header.magic != COREWAR_EXEC_MAGIC)
	{
		ft_fprintf(2, "Error: Couldn't recognise corewar exec magic\n");
		exit_vm(e, EXIT_FAILURE);
	}
	if (e->players[curr].header.prog_size != champ_size)
	{
		ft_fprintf(2, "Error: Champion size doesn't match prog size\n");
		exit_vm(e, EXIT_FAILURE);
	}
	char	buff[CHAMP_MAX_SIZE];
	int		i;
	int		position;

	if (read(fd, buff, champ_size) == champ_size)
	{
		i = 0;
		position = curr * (MEM_SIZE / e->players_nb);
		while (i < champ_size)
		{
			e->arena[POSMOD(position + i)].data = buff[i];
			i += 1;
		}

	}
	else
	{
		ft_fprintf(2, "Error: Unable to read predicted champ size\n");
		exit_vm(e, EXIT_FAILURE);
	}
}

void read_files(t_env *e)
{
	int curr;
	int fd;

	curr = 0;
	while (curr < e->players_nb)
	{
		if ((fd = open(e->players[curr].file, O_RDONLY)) == -1)
		{
			ft_fprintf(2, "Error: Couldn't read file %s.\n", e->players[curr].file);
			exit_vm(e, EXIT_FAILURE);
		}
		parse_file(e, fd, curr);
		close(fd);
		curr += 1;
	}
	//print_arena(e);
}
