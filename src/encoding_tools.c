#include "../includes/asm.h"

size_t djb_hash(const char* cp)
{
	size_t	hash;

	hash = 5381;
	while (*cp)
		hash = 33 * hash ^ (unsigned char)*cp++;
	return (hash);
}

int		nb_op(char *src)
{
	int	i;

	i = 0;
	while (op_tab[i].name)
	{
		if (djb_hash(src) == djb_hash(op_tab[i].name))
			break ;
		i++;
	}
	return (i);
}

void    write_byte(t_inst *inst, int32_t value, int32_t size)
{
	int		len;
	int8_t	i;
	int8_t	tmp;

	i = 0;
	inst->size += size - 1;
	len = inst->size - 1;
	while (size > 0)
	{
		tmp = ZMASK((value >> i));
		inst->tab[len + 1] = tmp;
		len--;
		i += 8;
		size--;
	}
}

void	get_binary(t_par *lst, t_inst *inst, int nb, int size)
{
	t_par	*tmp;
	int		i;
	int		bin;

	i = 0;
	bin = 6;
	tmp = lst;
	while (i < nb)
	{
		if (tmp->type == 1)
			inst->tab[size] = 0b01 << bin | inst->tab[size];
		else if (tmp->type == 2 || tmp->type == 3 || tmp->type == 5
				|| tmp->type == 15)
			inst->tab[size] = 0b10 << bin | inst->tab[size];
		else if (tmp->type == 4 || tmp->type == 9)
			inst->tab[size] = 0b11 << bin | inst->tab[size];
		tmp = tmp->next;
		bin -= 2;
		i++;
	}
	inst->size += 1;
}
