/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_logical_or.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 15:11:49 by jgossard          #+#    #+#             */
/*   Updated: 2025/07/30 20:13:51 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exec_logical_or(t_ast_node *node, t_shell *data, t_exec_context *context)
{
	int	result;

	if (!node || !data || !context)
		return (EXIT_FAILURE);
	result = ft_exec_node_recursive(node->left, data, context);
	// TODO: add waitpid
	if (result == EXIT_FAILURE)
	{
		return (ft_exec_node_recursive(node->right, data, context));
	}
	// if (context->input_fd != STDIN_FILENO)
	// 	close(context->input_fd);
	return (result);
}
