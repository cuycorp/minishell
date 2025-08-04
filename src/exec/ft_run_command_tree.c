/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run_command_tree.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 11:32:22 by jgossard          #+#    #+#             */
/*   Updated: 2025/07/31 11:46:33 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_run_command_tree(t_ast_node *root, t_shell *data)
{
	t_exec_context	*context;

	if (!root || !data)
		return (EXIT_FAILURE);
	context = ft_create_exec_context(root);
	if (!context)
	{
		ft_printf(STDERR_FILENO, "minishell: context structure creation failed: %s\n", strerror(errno));
		return (EXIT_FAILURE);
	}
	// Process Heredocs
	if (!ft_process_heredocs(root))
	{
		ft_free_exec_context(context);
		return (EXIT_FAILURE);
	}
	ft_exec_node_recursive(root, data, context);
	if (!ft_wait_all_pids(context))
	{
		dprintf(STDERR_FILENO, "ft_run_command_tree: issue with wait pid\n");
		return (EXIT_FAILURE);
	}
	ft_free_exec_context(context);
	return (context->last_exit_code);
}
/*
//         PIPE
//       /      \
//     PIPE     cmd3
//    /    \
//  cmd1  cmd2 */

// cat infile | ls | wc -l
