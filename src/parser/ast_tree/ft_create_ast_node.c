/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_ast_node.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 09:55:24 by jgossard          #+#    #+#             */
/*   Updated: 2025/07/01 11:30:57 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node	*ft_create_ast_node(t_ast_node_type type)
{
	t_ast_node	*node;

	node = ft_alloc_struct(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = type;
	return (node);
}
