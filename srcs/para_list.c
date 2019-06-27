/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   para_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandou <bghandou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 16:10:03 by bghandou          #+#    #+#             */
/*   Updated: 2019/06/27 17:09:39 by bghandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"

void	test_print(t_par *list)//delete when done!!
{
	while (list)
	{
		dprintf(1, "param : %s type : %d |||||||||| \n", list->param, list->type);
		list = list->next;
	}
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
