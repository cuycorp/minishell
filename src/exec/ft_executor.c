/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 11:32:22 by jgossard          #+#    #+#             */
/*   Updated: 2025/07/28 20:39:03 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	pipefd[0] refers to the read end of the pipe.
	pipefd[1] refers to the write end of the pipe.
*/

int	ft_execute_ast_tree(t_ast_node *node, t_shell *data, t_exec_context *context)
{
	if (!node || !data || !context) // TODO: check on current_infile_fd correct?
		return (EXIT_FAILURE);
	if (node->type == AST_PIPE)
		return (ft_exec_pipe_node(node, data, context));
	else if (node->type == AST_SIMPLE_COMMAND)
		return (ft_exec_simple_command(node->command_data, data,context));
	else if (node->type == AST_LOGICAL_AND)
		return (ft_exec_logical_and(node, data, context));
	else if (node->type == AST_LOGICAL_OR)
		return (ft_exec_logical_or(node, data, context));
	else if (node->type == AST_REDIRECTION)
		return (ft_exec_redirections(node->redirection_data, context));
	return (EXIT_FAILURE);
}

int	ft_executor(t_ast_node *root, t_shell *data)
{
	t_exec_context	*context;
	int	result;

	if (!root || !data) // TODO: add last_pid
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
	result = ft_execute_ast_tree(root, data, context);
	if (context->command_count > 0 && result == EXIT_SUCCESS)
		ft_wait_all_pids(data, context);
	ft_free_exec_context(context);
	return (result);
}
/*
//         PIPE
//       /      \
//     PIPE     cmd3
//    /    \
//  cmd1  cmd2 */

// cat infile | ls | wc -l
