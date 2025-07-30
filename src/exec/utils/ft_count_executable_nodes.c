/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_executable_nodes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 16:19:20 by jgossard          #+#    #+#             */
/*   Updated: 2025/07/30 10:38:25 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_executable_nodes(t_ast_node *node)
{
	if (!node)
		return (0);
	if (node->type == AST_SIMPLE_COMMAND)
		return (1);
	else if (node->type == AST_REDIRECTION)
		return (1);
	else if (node->type == AST_LOGICAL_AND || node->type == AST_LOGICAL_OR)
		return (ft_count_executable_nodes(node->left)
			+ ft_count_executable_nodes(node->right));
	else if (node->type == AST_PIPE)
		return (ft_count_executable_nodes(node->left)
			+ ft_count_executable_nodes(node->right));
	return (0);
}
