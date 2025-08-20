/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_simple_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 10:59:05 by jgossard          #+#    #+#             */
/*   Updated: 2025/08/20 16:10:42 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Executes a simple command in the child process.
 *
 * This function is meant to be called from a forked child process. It prepares
 * the input/output file descriptors for redirection and pipes, handles signal
 * behavior for the child, and executes either a built-in or external command.
 *
 * @param command Pointer to the simple command node in the AST.
 * @param data Pointer to the global shell state, including execution context.
 *
 * The function performs the following steps:
 * - Verifies validity of input parameters.
 * - Sets the child-specific signal handlers.
 * - Prepares I/O redirections (including heredocs and regular redirections).
 * - Applies the necessary file descriptor duplications (dup2) for stdin/stdout.
 * - Closes all heredoc file descriptors from the AST.
 * - Executes either a shell built-in command or an external binary.
 * - Exits the child process with the returned exit status.
 *
 * @note This function will call _exit() and never return.
 */
static void	ft_exec_simple_command_child(t_command *command, t_shell *data)
{
	t_exec_context	*context;
	int				exit_code;

	if (!command || !data || !data->context)
		ft_exit_child(data, EXIT_FAILURE);
	ft_set_signal_child(true);
	context = data->context;
	if (!ft_prepare_command_io(command->redirection, context))
		ft_exit_child(data, EXIT_FAILURE);
	ft_handle_dup2_and_close_fd(context->input_fd, STDIN_FILENO, data);
	ft_handle_dup2_and_close_fd(context->output_fd, STDOUT_FILENO, data);
	ft_close_heredocs_fd(data->ast_root);
	if (ft_is_child_builtin(command->name))
		exit_code = ft_exec_child_builtin(command, data);
	else
		exit_code = ft_exec_external_command(command, data);
	ft_exit_child(data, exit_code);
}

/**
 * @brief Executes the parent-side logic for a simple command after forking.
 *
 * This function is called in the parent process after a fork has been done
 * to execute a simple command. It waits for the child process to finish,
 * restores signal handling, and returns the appropriate exit status.
 *
 * @param command Pointer to the command structure representing the command.
 * @param data Pointer to the global shell state, including execution context.
 * @param pid Process ID of the child process to wait for.
 * @param sig Struct containing the original signal state to restore.
 *
 * @return EXIT_SUCCESS on successful wait and signal restoration,
 *         or EXIT_FAILURE on error.
 */
static int	ft_exec_simple_command_parent(t_command *command, t_shell *data,
		int pid, t_signal_child sig)
{
	t_exec_context	*context;

	if (!command || !data || !data->context || pid < 0)
		return (EXIT_FAILURE);
	context = data->context;
	if (waitpid(pid, &context->last_exit_code, 0) == -1)
	{
		ft_error_failed_waitpid("ft_exec_simple_command_parent");
		return (EXIT_FAILURE);
	}
	ft_restore_signal_parent_simple_command(&sig, data);
	return (EXIT_SUCCESS);
}

/**
 * @brief Executes a simple command node (non-pipeline) in the shell.
 *
 * This function determines whether the command is a built-in that should be
 * executed in the parent process or a normal command that requires forking.
 * If it is a parent built-in and input redirection is not involved, the command
 * is executed directly. Otherwise, it forks and handles execution accordingly.
 * It sets up the necessary execution context and handles
 * signal masking during the fork/exec sequence.
 *
 * @param command Pointer to the command AST node to execute.
 * @param data Pointer to the shell state containing execution context and AST.
 *
 * @return int Exit status of the command.
 *         - Returns the exit code of the executed command.
 *         - Returns EXIT_FAILURE on error (e.g., failed fork or invalid input).
 *
 * The function performs the following:
 * - Verifies command and context validity.
 * - Checks if the command is a "parent-handled" builtin (like `cd`, `export`).
 *     - If so, and there's no input redirection/piping, it executes immediately
 *       in the parent process without forking.
 * - Otherwise:
 *     - Sets signal handling for the parent (blocking SIGINT, etc.).
 *     - Forks a child process.
 *     - The child handles redirection/heredoc cleanup and delegates to
 *       `ft_exec_simple_command_child()`.
 *     - The parent waits for the child via `ft_exec_simple_command_parent()`.
 *
 * @note This function is typically used when executing a simple command node
 *       in the AST (not a pipe or sequence).
 */
int	ft_exec_simple_command(t_command *command, t_shell *data)
{
	t_exec_context	*context;
	pid_t			pid;
	bool			is_parent_builtin;
	t_signal_child	sig;

	if (!command || !data || !data->context)
		return (EXIT_FAILURE);
	context = data->context;
	is_parent_builtin = ft_is_parent_builtin(command->name);
	if (is_parent_builtin && context->input_fd == STDIN_FILENO)
	{
		data->exit_code = ft_exec_parent_builtin(command, data);
		return (data->exit_code);
	}
	ft_set_signal_parent(&sig);
	pid = fork();
	if (pid < 0)
		return (ft_error_failed_to_fork("ft_exec_simple_comand"), EXIT_FAILURE);
	if (pid == 0)
	{
		if (!command->redirection)
			ft_close_heredocs_fd(data->ast_root);
		ft_exec_simple_command_child(command, data);
	}
	return (ft_exec_simple_command_parent(command, data, pid, sig));
}
