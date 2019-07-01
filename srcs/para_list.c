/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   para_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandou <bghandou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 16:10:03 by bghandou          #+#    #+#             */
/*   Updated: 2019/07/01 16:12:29 by bghandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"

void	test_print(t_par *list)//delete when done!!
{
	char *str;

	dprintf(1, "________________\n");
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
		if (list->type == 15 || list->type == 5 || list-> type == 9)
			dprintf(1, " ---> Pointing to :%s_type:%d", list->lbl_ptr->param, list->lbl_ptr->type);
		dprintf(1, "\n");
		list = list->next;
	}
	dprintf(1, "______________\n");
	dprintf(1, "\n");
}

t_par	*add_parameter(t_par *list, char *inst, int type)
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
		list->lbl_ptr = NULL;
		list->next = NULL;
		head = list;
	}
	else
	{
		tmp = list;
		if (!(tmp = malloc(sizeof(t_par))))
			return (NULL);
		tmp->param = ft_strdup(inst);
		tmp->type = type;
		tmp->lbl_ptr = NULL;
		tmp->next = NULL;
		while (list->next)
			list = list->next;
		list->next = tmp;
	}
	return (head);
}
