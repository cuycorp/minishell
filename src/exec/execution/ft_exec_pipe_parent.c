/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_pipe_parent.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 16:59:47 by jgossard          #+#    #+#             */
/*   Updated: 2025/08/25 17:33:15 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static pid_t	ft_fork_and_exec_right(t_pipe_exec_data *exec_data)
{
	pid_t	right_pid;
	int		status_right;

	if (!exec_data || !exec_data->root || !exec_data->data
		|| !exec_data->context || !exec_data->pipe_fd
		|| exec_data->left_pid < 0)
		return (-1);
	right_pid = fork();
	if (right_pid < 0)
	{
		close(exec_data->pipe_fd[READ_END]);
		ft_error_failed_to_fork("ft_exec_pipe_parent (right fork)");
		waitpid(exec_data->left_pid, NULL, 0);
		return (-1);
	}
	if (right_pid == 0)
	{
		status_right = ft_exec_node_recursive(exec_data->root->right,
				exec_data->data, exec_data->context);
		ft_exit_child(exec_data->data, status_right);
	}
	return (right_pid);
}

static int	ft_handle_child_exit_statuses(t_shell *data,
		t_exec_context *context, pid_t left_pid, pid_t right_pid)
{
	int	status_left;

	if (!data || !context || left_pid < 0 || right_pid < 0)
	{
		if (data)
			data->exit_code = EXIT_FAILURE;
		return (EXIT_FAILURE);
	}
	if (waitpid(left_pid, &status_left, 0) == -1)
	{
		data->exit_code = EXIT_FAILURE;
		return (EXIT_FAILURE);
	}
	if (waitpid(right_pid, &context->last_exit_code, 0) == -1)
	{
		ft_error_failed_waitpid("ft_exec_pipe_parent");
		data->exit_code = EXIT_FAILURE;
		return (EXIT_FAILURE);
	}
	return (0);
}

static void	ft_apply_exit_status(t_shell *data, t_exec_context *context)
{
	if (g_exit_code != -1)
		data->exit_code = g_exit_code;
	else
		data->exit_code = ft_handle_child_exit_status(context->last_exit_code);
	g_exit_code = -1;
}

static int	ft_setup_pipe_fds(t_exec_context *context, int *pipe_fd)
{
	if (!context || !pipe_fd)
		return (EXIT_FAILURE);
	close(pipe_fd[WRITE_END]);
	if (context->input_fd != STDIN_FILENO)
		ft_safe_close_and_reset_fd(&context->input_fd);
	context->input_fd = pipe_fd[READ_END];
	return (EXIT_SUCCESS);
}

/**
 * @brief Handles the parent side of a pipe execution in a shell AST.
 *
 * After the left child process has been forked and executed, this function:
 * - Closes the write end of the pipe.
 * - Prepares input for the right side of the pipe.
 * - Forks and executes the right child node of the pipe AST.
 * - Waits for both child processes (left and right).
 * - Finalizes the shell's exit code based on child statuses or global signals.
 *
 * @param root     AST node representing the pipe operator.
 * @param data     Pointer to the shell state.
 * @param left_pid PID of the previously forked left child process.
 * @param pipe_fd  Pipe file descriptors [READ_END, WRITE_END].
 *
 * @return Exit code of the right child or computed shell exit code.
 *
 * @note Properly closing unused pipe ends is critical to avoid:
 * - Hanging reads (due to open write ends)
 * - Resource leaks in large pipelines
 */
int	ft_exec_pipe_parent(t_ast_node *root, t_shell *data, pid_t left_pid,
		int *pipe_fd)
{
	t_pipe_exec_data	exec_data;
	pid_t				right_pid;

	if (!pipe_fd)
		ft_exit_child(data, EXIT_FAILURE);
	if (!root || !data || !data->context || left_pid < 0)
	{
		ft_close_pipe_fds(pipe_fd);
		ft_exit_child(data, EXIT_FAILURE);
	}
	exec_data.root = root;
	exec_data.data = data;
	exec_data.context = data->context;
	exec_data.pipe_fd = pipe_fd;
	exec_data.left_pid = left_pid;
	if (ft_setup_pipe_fds(exec_data.context, pipe_fd) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	right_pid = ft_fork_and_exec_right(&exec_data);
	if (right_pid < 0)
		return (EXIT_FAILURE);
	ft_safe_close_and_reset_fd(&exec_data.context->input_fd);
	if (ft_handle_child_exit_statuses(data, exec_data.context, left_pid,
			right_pid) != 0)
		return (EXIT_FAILURE);
	return (ft_apply_exit_status(data, exec_data.context), data->exit_code);
}
