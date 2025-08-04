/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_ast_tree.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:26:04 by mcamaren          #+#    #+#             */
/*   Updated: 2025/08/04 11:20:50 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_free_ast_node(t_ast_node *node)
{
	if (node != NULL)
	{
		if (node->value)
		{
			free(node->value);
			node->value = NULL;
		}
		if (node->redirection_data)
			ft_free_redirection(&node->redirection_data);
		if (node->command_data)
		{
			ft_free_command(node->command_data);
			node->command_data = NULL;
		}
		free(node);
	}
}

void	ft_free_ast_tree(t_ast_node **root)
{
	if (!root || *root == NULL)
		return ;
	ft_free_ast_tree(&(*root)->left);
	ft_free_ast_tree(&(*root)->right);
	ft_free_ast_node(*root);
	*root = NULL;
}
