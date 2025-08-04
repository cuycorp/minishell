/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_logical_or.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 15:11:49 by jgossard          #+#    #+#             */
/*   Updated: 2025/08/04 14:52:05 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exec_logical_or(t_ast_node *node, t_shell *data, t_exec_context *context)
{
	if (!node || !data || !context)
		return (EXIT_FAILURE);
	ft_exec_node_recursive(node->left, data, context);
	if (!ft_wait_all_pids(context))
	{
		dprintf(STDERR_FILENO, "ft_exec_logical_and: issue with wait pid\n"); // TODO: remove this dprintf
		return (EXIT_FAILURE);
	}
	ft_mark_pids_reaped(context);
	if (context->last_exit_code == EXIT_FAILURE)
		return (ft_exec_node_recursive(node->right, data, context));
	return (context->last_exit_code);
}
