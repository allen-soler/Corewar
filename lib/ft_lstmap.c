/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 10:04:12 by bghandou          #+#    #+#             */
/*   Updated: 2018/11/15 12:09:14 by bghandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*newlist;
	t_list	*prev;
	t_list	*nxt;

	prev = NULL;
	newlist = NULL;
	while (lst && f)
	{
		nxt = f(lst);
		nxt->next = NULL;
		if (newlist == NULL)
		{
			newlist = nxt;
			prev = nxt;
		}
		else
		{
			prev->next = nxt;
			prev = nxt;
		}
		lst = lst->next;
	}
	return (newlist);
}
