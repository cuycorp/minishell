/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_ast_node.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:12:12 by jgossard          #+#    #+#             */
/*   Updated: 2025/07/01 11:30:51 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node	*ft_add_ast_node(
	t_ast_node_type type, t_ast_node *left, t_ast_node *right)
{
	t_ast_node	*node;

	if (!type || !left || !right)
		return (NULL);
	node = ft_create_ast_node(type);
	if (!node)
		return (NULL);
	node->left = left;
	node->right = right;
	return (node);
}
