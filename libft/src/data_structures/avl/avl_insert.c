/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avl_insert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalonso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 16:46:16 by nalonso           #+#    #+#             */
/*   Updated: 2019/05/31 16:46:48 by nalonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "avl.h"

t_avl_node	*avl_right_rotate(t_avl_node *root)
{
	t_avl_node *left_child;
	t_avl_node *temp;

	left_child = root->left;
	temp = left_child->right;
	left_child->right = root;
	root->left = temp;
	root->height = ft_max(avl_height(root->left), avl_height(root->right)) + 1;
	left_child->height =\
	ft_max(avl_height(left_child->left), avl_height(left_child->right)) + 1;
	return (left_child);
}

t_avl_node	*avl_left_rotate(t_avl_node *root)
{
	t_avl_node	*right_child;
	t_avl_node	*temp;

	right_child = root->right;
	temp = right_child->left;
	right_child->left = root;
	root->right = temp;
	root->height = ft_max(avl_height(root->left), avl_height(root->right)) + 1;
	right_child->height =\
	ft_max(avl_height(right_child->left), avl_height(right_child->right)) + 1;
	return (right_child);
}

int			avl_insert(t_avl *self, unsigned long key, int index)
{
	t_avl_node *tmp;

	tmp = avl_insert_node(self->head, key, index);
	if (tmp == NULL)
	{
		avl_free(self->head);
		return (0);
	}
	self->head = tmp;
	return (1);
}
