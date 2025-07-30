/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_logical_and.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 15:11:35 by jgossard          #+#    #+#             */
/*   Updated: 2025/07/30 20:14:01 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exec_logical_and(t_ast_node *node, t_shell *data,
		t_exec_context *context)
{
	int	result;

	if (!node || !data || !context)
		return (EXIT_FAILURE);
	result = ft_exec_node_recursive(node->left, data, context);
	// TODO: add waitpid
	if (result == EXIT_SUCCESS)
	{
		context->input_fd = STDIN_FILENO;
		return (ft_exec_node_recursive(node->right, data, context));
	}
	// if (context->input_fd != STDIN_FILENO)
	// 	close(context->input_fd);
	return (result);
}
