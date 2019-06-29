/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 12:29:19 by bghandou          #+#    #+#             */
/*   Updated: 2018/11/14 23:25:57 by bghandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void*, size_t))
{
	t_list	*temp;

	if (*alst == NULL)
		return ;
	else
	{
		temp = *alst;
		while (temp)
		{
			del(temp->content, temp->content_size);
			free(temp);
			temp = temp->next;
		}
		*alst = NULL;
	}
}
