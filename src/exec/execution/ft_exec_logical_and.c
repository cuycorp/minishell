/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_logical_and.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 15:11:35 by jgossard          #+#    #+#             */
/*   Updated: 2025/08/20 15:41:04 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exec_logical_and(t_ast_node *node, t_shell *data,
		t_exec_context *context)
{
	if (!node || !data || !context)
		return (EXIT_FAILURE);
	ft_exec_node_recursive(node->left, data, context);
	if (context->last_exit_code == EXIT_SUCCESS)
	{
		ft_reset_context_fds(context);
		return (ft_exec_node_recursive(node->right, data, context));
	}
	return (context->last_exit_code);
}
