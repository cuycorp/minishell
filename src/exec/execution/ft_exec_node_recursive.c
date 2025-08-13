/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_node_recursive.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 09:28:15 by jgossard          #+#    #+#             */
/*   Updated: 2025/08/12 00:59:31 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exec_node_recursive(t_ast_node *node, t_shell *data,
	t_exec_context *context)
{
	if (!node || !data || !context)
		return (EXIT_FAILURE);
	if (node->type == AST_PIPE)
		return (ft_exec_pipe_node(node, data));
	else if (node->type == AST_SIMPLE_COMMAND)
		return (ft_exec_simple_command(node->command_data, data));
	else if (node->type == AST_LOGICAL_AND)
		return (ft_exec_logical_and(node, data, context));
	else if (node->type == AST_LOGICAL_OR)
		return (ft_exec_logical_or(node, data, context));
	else if (node->type == AST_REDIRECTION)
	{
		//todo: remove the ft_process_heredocs
		if (!ft_process_heredocs(node, data))
		{
			ft_free_exec_context(data->context);
			return (EXIT_FAILURE);
		}
		return (ft_exec_redirections(node->redirection_data, data));
	}
	return (EXIT_FAILURE);
}
