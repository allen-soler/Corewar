/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalonso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 16:11:57 by nalonso           #+#    #+#             */
/*   Updated: 2018/11/07 16:46:08 by nalonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*ptr;

	ptr = NULL;
	if (lst && f)
	{
		if (!(ptr = f(lst)))
		{
			free(ptr);
			return (NULL);
		}
		ptr->next = ft_lstmap(lst->next, f);
		return (ptr);
	}
	return (NULL);
}
