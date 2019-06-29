/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avl_norme.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalonso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 16:46:21 by nalonso           #+#    #+#             */
/*   Updated: 2019/05/31 16:49:00 by nalonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "avl.h"

static t_avl_node	*avl_insert_node_norme(t_avl_node *node,\
									unsigned long key)
{
	int balance;

	node->height = 1 + ft_max(avl_height(node->left), avl_height(node->right));
	balance = avl_get_balance(node);
	if (balance > 1 && key < node->left->key)
		return (avl_right_rotate(node));
	if (balance < -1 && key > node->right->key)
		return (avl_left_rotate(node));
	if (balance > 1 && key > node->left->key)
	{
		node->left = avl_left_rotate(node->left);
		return (avl_right_rotate(node));
	}
	if (balance < -1 && key < node->right->key)
	{
		node->right = avl_right_rotate(node->right);
		return (avl_left_rotate(node));
	}
	return (node);
}

t_avl_node			*avl_insert_node(t_avl_node *node,\
								unsigned long key, int index)
{
	if (node == NULL)
		return (new_avl_node(key, index));
	if (key < node->key)
	{
		node->left = avl_insert_node(node->left, key, index);
		if (node->left == NULL)
			return (NULL);
	}
	else if (key > node->key)
	{
		node->right = avl_insert_node(node->right, key, index);
		if (node->right == NULL)
			return (NULL);
	}
	else
	{
		ft_putendl_fd("ERROR", 2);
		exit(1);
		return (NULL);
	}
	return (avl_insert_node_norme(node, key));
}

int					avl_height(t_avl_node *n)
{
	if (n == NULL)
		return (0);
	return (n->height);
}

int					avl_get_balance(t_avl_node *n)
{
	if (n == NULL)
		return (0);
	return (avl_height(n->left) - avl_height(n->right));
}
