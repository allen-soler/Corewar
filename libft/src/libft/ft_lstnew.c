/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalonso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 15:28:39 by nalonso           #+#    #+#             */
/*   Updated: 2019/02/09 19:11:29 by nalonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list *new;

	new = (t_list *)malloc(sizeof(*new));
	if (new != NULL)
	{
		if (!content)
		{
			new->content = NULL;
			new->content_size = 0;
		}
		else
		{
			if ((new->content = malloc(content_size + 1)) == NULL)
			{
				free(new);
				return (NULL);
			}
			new->content = ft_memcpy(new->content, content, content_size);
			new->content_size = content_size;
		}
		new->next = NULL;
	}
	return (new);
}
