/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_pipe_node.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 15:07:24 by jgossard          #+#    #+#             */
/*   Updated: 2025/08/25 17:42:50 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Executes the left side of the pipe in the child process.
 *
 * This function is executed inside the forked child process. It:
 * - Closes the unused read end of the pipe.
 * - Redirects STDOUT to the write end of the pipe.
 * - If input redirection is set (i.e., context->input_fd != STDIN),
 *   it redirects STDIN accordingly.
 * - Executes the left subtree of the AST.
 *
 * @param root     The AST node (pipe).
 * @param data     Shell state.
 * @param context  Execution context.
 * @param pipe_fd  Pipe file descriptors [READ, WRITE].
 *
 * @note
 * 1. `dup2(pipe_fd[WRITE_END], STDOUT_FILENO)`:
 *    Redirects the output of the current command to the write end of the pipe.
 *    This means whatever the command prints to STDOUT goes to the next process.
 *
 * 2. `if (context->input_fd != STDIN_FILENO)`:
 *    If the input was previously redirected (from a previous pipe or file),
 *    we must duplicate that FD to STDIN so this command reads correctly.
 *
 * 3. `close()` calls after `dup2()`:
 *    We close the FDs because `dup2()` duplicates them;
 *    the original FD is no longer needed. This prevents FD leaks.
 */
static void	ft_exec_pipe_child(t_ast_node *root, t_shell *data, int *pipe_fd)
{
	t_exec_context	*context;
	int				exit_code;

	if (!root || !data || !data->context)
	{
		ft_close_pipe_fds(pipe_fd);
		ft_exit_child(data, EXIT_FAILURE);
	}
	if (!pipe_fd)
		ft_exit_child(data, EXIT_FAILURE);
	context = data->context;
	close(pipe_fd[READ_END]);
	if (context->output_fd != STDOUT_FILENO
		&& context->output_fd > STDERR_FILENO)
		ft_safe_close_and_reset_fd(&context->output_fd);
	ft_handle_dup2_and_close_fd(pipe_fd[WRITE_END], STDOUT_FILENO, data);
	if (context->input_fd != STDIN_FILENO)
	{
		ft_handle_dup2_and_close_fd(context->input_fd, STDIN_FILENO, data);
		context->input_fd = STDIN_FILENO;
	}
	exit_code = ft_exec_node_recursive(root->left, data, context);
	ft_exit_child(data, exit_code);
}

int	ft_exec_pipe_node(t_ast_node *root, t_shell *data)
{
	pid_t			pid;
	int				pipe_fd[2];

	if (!root || !data)
		return (EXIT_FAILURE);
	if (pipe(pipe_fd) == -1)
	{
		ft_error_failed_to_pipe("ft_exec_pipe_node");
		return (EXIT_FAILURE);
	}
	pid = fork();
	if (pid < 0)
	{
		ft_close_pipe_fds(pipe_fd);
		ft_error_failed_to_fork("ft_exec_pipe_node");
		return (EXIT_FAILURE);
	}
	if (pid == 0)
		ft_exec_pipe_child(root, data, pipe_fd);
	return (ft_exec_pipe_parent(root, data, pid, pipe_fd));
}

/*
//       PIPE
//      /    \
//    PIPE   cmd1
//   /    \
// cmd2   cmd3
*/

/*
//       Simple_Command
//      /    \
//    PIPE   cmd1
//   /    \
// cmd2   cmd3
*/
