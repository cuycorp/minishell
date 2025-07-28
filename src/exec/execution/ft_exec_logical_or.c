/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_logical_or.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 15:11:49 by jgossard          #+#    #+#             */
/*   Updated: 2025/07/28 19:46:09 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exec_logical_or(t_ast_node *node, t_shell *data, t_exec_context *context)
{
	int	result;

	if (!node || !data || !context)
		return (EXIT_FAILURE);
	result = ft_execute_ast_tree(node->left, data, context);
	if (result == EXIT_FAILURE)
		return (ft_execute_ast_tree(node->right, data, context));
	if (context->input_fd != STDIN_FILENO)
		close(context->input_fd);
	return (result);
}
