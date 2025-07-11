/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 11:32:22 by jgossard          #+#    #+#             */
/*   Updated: 2025/07/28 12:14:07 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	pipefd[0] refers to the read end of the pipe.
	pipefd[1] refers to the write end of the pipe.
*/

int	ft_execute_ast_tree(t_ast_node *node, t_shell *data,
		int input_fd, int *last_pid)
{
	if (!node || !data || !last_pid || input_fd < 0) // TODO: check on current_infile_fd correct?
		return (EXIT_FAILURE);
	if (node->type == AST_PIPE)
		return (ft_exec_pipe_node(node, data, input_fd, last_pid));
	else if (node->type == AST_SIMPLE_COMMAND)
		return (ft_exec_simple_command(node->command_data, data, input_fd, last_pid));
	else if (node->type == AST_LOGICAL_AND)
		return (ft_exec_logical_and(node, data, input_fd, last_pid));
	else if (node->type == AST_LOGICAL_OR)
		return (ft_exec_logical_or(node, data, input_fd, last_pid));
	else if (node->type == AST_REDIRECTION)
		return (ft_exec_redirections(node->redirection_data));
	return (EXIT_FAILURE);
}

int	ft_executor(t_ast_node *root, t_shell *data)
{
	int	last_pid;
	int	result;

	if (!root || !data) // TODO: add last_pid
		return (EXIT_FAILURE);
	last_pid = -1;
	data->pid_count = 0;
	data->command_count = ft_count_cmd_nodes(data->ast_root);
	data->pids = malloc(sizeof(pid_t) * data->command_count);
	if (!data->pids)
		return (perror("Error: malloc failed"), EXIT_FAILURE);
	// Process Heredocs
	if (!ft_process_heredocs(root))
		return (EXIT_FAILURE);
	result = ft_execute_ast_tree(root, data, STDIN_FILENO, &last_pid);
	if (data->command_count > 0 && result == EXIT_SUCCESS)
		ft_wait_all_pids(data, &last_pid);
	return (result);
}
/*
//         PIPE
//       /      \
//     PIPE     cmd3
//    /    \
//  cmd1  cmd2 */

// cat infile | ls | wc -l
