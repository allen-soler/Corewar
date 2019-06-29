/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalonso <nalonso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 16:32:03 by nalonso           #+#    #+#             */
/*   Updated: 2019/05/31 16:42:20 by nalonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "avl.h"

void		*avl_free(t_avl_node *node)
{
	if (!node)
		return (NULL);
	avl_free(node->left);
	avl_free(node->right);
	free(node);
	return (NULL);
}

t_avl_node	*new_avl_node(unsigned long key, int index)
{
	t_avl_node	*node;

	node = malloc(sizeof(t_avl_node));
	if (!node)
		return (NULL);
	node->height = 0;
	node->key = key;
	node->index = index;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

int			avl_get_index(t_avl_node *root, unsigned long key)
{
	if (root == NULL)
		return (-1);
	if (key < root->key)
		return (avl_get_index(root->left, key));
	else if (key > root->key)
		return (avl_get_index(root->right, key));
	else
		return (root->index);
}

t_avl		avl_init(void)
{
	t_avl n;

	n.head = NULL;
	n.free = avl_free;
	n.insert = avl_insert;
	n.get_index = avl_get_index;
	return (n);
}
