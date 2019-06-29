#include "../includes/vm.h"

static void parse_file(t_env *env, int fd, int curr)
{
	size_t	offset;
	size_t	size;
	size_t	i;
	size_t	position;

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
	env->players[curr].header.prog_size = offset;
	if (lseek(fd, sizeof(header_t), SEEK_SET) == sizeof(header_t))
	{
		position = curr * (MEM_SIZE / env->players_nb);
		i = 0;
		while (i <= offset)
		{
			if (read(fd, &(env->arena[position + i].data), 1) < 0)
			{
				ft_fprintf(2, "Error: Couldn't read file %s.\n",\
					env->players[curr].file);
				exit_vm(env, EXIT_FAILURE);
			}
			env->arena[position + i].player = curr;
			i += 1;
		}
	}
}

void print_arena(t_env *e)
{
	size_t	i;
	size_t	line;

	i = 0;
	line = 0;
	while (i < MEM_SIZE)
	{
		if (i % 32 == 0)
		{
			ft_printf("0x%04x : ", line);
			line += 32;
		}
		if (g_debug == 0)
			ft_printf("%02hhx ", e->arena[i++].data);
		else if (e->arena[i].player == 0)
			ft_printf("{r}%02hhx{R} ", e->arena[i++].data);
		else if (e->arena[i].player == 1)
			ft_printf("{b}%02hhx{R} ", e->arena[i++].data);
		else if (e->arena[i].player == 2)
			ft_printf("{g}%02hhx{R} ", e->arena[i++].data);
		else if (e->arena[i].player == 3)
			ft_printf("{y}%02hhx{R} ", e->arena[i++].data);
		else
			ft_printf("%02hhx ", e->arena[i++].data);
		if (i % 32 == 0)
			ft_putendl(0);
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
