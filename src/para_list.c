/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   para_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandou <bghandou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 16:10:03 by bghandou          #+#    #+#             */
/*   Updated: 2019/07/09 12:18:43 by bghandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void	fix_leak(t_par **list, intmax_t stock, int n, int row)
{
	char	*dest;

	dest = ft_itoa(stock);
	*list = add_parameter(*list, dest, n, row);
	free(dest);
}

void	test_print(t_par *list)//delete when done!!
{
	char *str;

	//dprintf(1, "________________\n");
	while (list)
	{
		if (list->type == 1)
			str = "REG";
		else if (list->type == 2)
			str = "DIR_2Bytes";
		else if (list->type == 3)
			str = "DIR_4Bytes";
		else if (list->type == 4)
			str = "INDIRECT";
		else if (list->type == 5)
			str = "DIR_LABEL4Bytes";
		else if (list->type == 6)
			str = "INSTRUCT";
		else if (list->type ==7)
			str = "LABEL";
		else if (list->type == 8)
			str = "COMMENT!";
		else if (list->type == 9)
			str = "IND_LABEL";
		else if (list->type == 15)
			str = "DIR_LABEL2Bytes";
		else
			str = "UNDEF";
		dprintf(1, " param : '%s'		type : %s", list->param, str);
	//	if (list->type == 15 || list->type == 5 || list-> type == 9)
	//		dprintf(1, " ---> Pointing to :%s_type:%d", list->lbl_ptr->param, list->lbl_ptr->type);
		dprintf(1, "\n");
		list = list->next;
	}
	dprintf(1, "______________\n");
	dprintf(1, "\n");
}

static void	add_par_extra(t_par *list, char *inst, int type, int row)
{
	t_par *tmp;

	tmp = list;
	if (!(tmp = malloc(sizeof(t_par))))
		return ;
	tmp->param = ft_strdup(inst);
	tmp->type = type;
	tmp->row = row;
	tmp->cnt = 0;
	tmp->pos = 0;
	tmp->lbl_ptr = NULL;
	tmp->next = NULL;
	while (list->next)
		list = list->next;
	list->next = tmp;
}

t_par	*add_parameter(t_par *list, char *inst, int type, int row)
{
	t_par	*tmp;
	t_par	*head;

	head = list;
	tmp = NULL;
//	dprintf(1, "=======ADDED : %s, type:%d\n", inst, type);
	if (!list)
	{
		if (!(list = malloc(sizeof(t_par))))
			return (NULL); 
		list->param = ft_strdup(inst);
		list->type = type;
		list->row = row;
		list->lbl_ptr = NULL;
		list->next = NULL;
		head = list;
	}
	else
		add_par_extra(list, inst, type, row);
	return (head);
}
