/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_pipe_node.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 15:07:24 by jgossard          #+#    #+#             */
/*   Updated: 2025/08/05 09:57:25 by jgossard         ###   ########.fr       */
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
		ft_close_fds(pipe_fd);
		ft_exit_child(data, EXIT_FAILURE);
	}
	if (!pipe_fd)
		ft_exit_child(data, EXIT_FAILURE);
	context = data->context;
	close(pipe_fd[READ_END]);
	if (!ft_apply_dup2(pipe_fd[WRITE_END], STDOUT_FILENO))
		ft_exit_child(data, EXIT_FAILURE);
	close(pipe_fd[WRITE_END]);
	if (context->input_fd != STDIN_FILENO)
	{
		if (!ft_apply_dup2(context->input_fd, STDIN_FILENO))
			ft_exit_child(data, EXIT_FAILURE);
		close(context->input_fd);
	}
	exit_code = ft_exec_node_recursive(root->left, data, context);
	ft_exit_child(data, exit_code);
}

/**
 * @brief Parent process handler after forking a pipe.
 *
 * Performs cleanup and launches the right subtree of the pipe AST.
 *
 * @param root     Current AST node.
 * @param data     Shell state.
 * @param context  Execution context.
 * @param pid      PID of the forked child process.
 * @param pipe_fd  Pipe file descriptors [READ, WRITE].
 *
 * @return Result of executing the right side of the pipe.
 *
 * @note
 * If the parent process doesn’t close the previous input FD (used by the left
 * command), it will remain open. This can:
 * - Cause the pipe's read end to never receive EOF, making read() hang.
 * - Lead to too many open file descriptors in long pipelines.
 */
static int	ft_exec_pipe_parent(t_ast_node *root, t_shell *data, pid_t pid, int *pipe_fd)
{
	t_exec_context	*context;
	int				result;

	if (!pipe_fd)
		ft_exit_child(data, EXIT_FAILURE);
	if (!root || !data || !data->context || pid < 0)
	{
		ft_close_fds(pipe_fd);
		ft_exit_child(data, EXIT_FAILURE);
	}
	context = data->context;
	close(pipe_fd[WRITE_END]);
	if (context->input_fd != STDIN_FILENO)
		close(context->input_fd);
	// Add child PID to tracking
	if (context->pid_count < context->command_count)
		context->pids[context->pid_count++] = pid;
	context->last_pid = pid;
	context->input_fd = pipe_fd[READ_END];
	result = ft_exec_node_recursive(root->right, data, context);
	close(pipe_fd[READ_END]);
	return (result);
}

int	ft_exec_pipe_node(t_ast_node *root, t_shell *data)
{
	pid_t			pid;
	int				pipe_fd[2];

	if (!root || !data)
		return (EXIT_FAILURE);
	if (pipe(pipe_fd) == -1)
		return (perror("Pipe failed!"), EXIT_FAILURE);
	pid = fork();
	if (pid < 0)
	{
		ft_close_fds(pipe_fd);
		if (data->context && data->context->input_fd != STDIN_FILENO)
			close(data->context->input_fd);
		return (perror("failed to fork"), EXIT_FAILURE);
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
