/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_simple_command_node.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 09:55:24 by jgossard          #+#    #+#             */
/*   Updated: 2025/06/30 10:08:25 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node	*ft_create_simple_command_node(t_command *command)
{
	t_ast_node	*node;

	node = ft_alloc_struct(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = AST_SIMPLE_COMMAND;
	node->command_data = command;
	node->redirection_data = NULL;
	return (node);
}
