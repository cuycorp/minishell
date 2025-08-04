/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_simple_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 10:59:05 by jgossard          #+#    #+#             */
/*   Updated: 2025/07/31 20:11:38 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_exec_simple_command_child(t_command *command, t_shell *data,
		t_exec_context *context, bool flag_sigquit)
{
	if (!command || !data || !context)
		exit(EXIT_FAILURE);
	// Prepare redirection
	dprintf(STDERR_FILENO, "ft_exec_simple_command_child: in function\n");

	ft_set_signal_child(flag_sigquit);
	if (!ft_prepare_command_io(command->redirection, context))
		exit(EXIT_FAILURE);
	// Apply pipe or redirection fds
	if (context->input_fd != STDIN_FILENO)
	{
		if (!ft_apply_dup2(context->input_fd, STDIN_FILENO))
			exit(EXIT_FAILURE);
		close(context->input_fd);
	}
	if (context->output_fd != STDOUT_FILENO)
	{
		if (!ft_apply_dup2(context->output_fd, STDOUT_FILENO))
			exit(EXIT_FAILURE);
		close(context->output_fd);
	}
	// TODO: fix issue with exit_code here
	dprintf(STDERR_FILENO, "ft_exec_simple_command_child: end function\n");
	if (ft_is_child_builtin(command->name))
		exit(ft_exec_child_builtin(command, data));
	else
		exit(ft_exec_external_command(command, data));
}

static int	ft_exec_simple_command_parent(t_command *command,
		t_exec_context *context, int pid, t_signal_child sig)
{
	if (!command || !context || pid < 0)
		return (EXIT_FAILURE);
	dprintf(STDERR_FILENO, "ft_exec_simple_command: in function\n");
	if (context->input_fd != STDIN_FILENO)
		close(context->input_fd);
	if (context->output_fd != STDOUT_FILENO)
		close(context->output_fd);
	// if (context->pid_count < context->command_count)
	// {
	// 	context->pids[context->pid_count] = pid;
	// 	// context->pid_count++;
	// 	context->last_pid = pid;
	// }
	if (ft_waitpid(pid, context) == false)
	{
		dprintf(STDERR_FILENO, "ft_exec_simple_command: waitpid failed\n");
		return (EXIT_FAILURE);
	}
	ft_restore_signal_parent_n_exit_simple_command(&sig, context);
	dprintf(STDERR_FILENO, "ft_exec_simple_command: end of function\n");
	return (EXIT_SUCCESS);
}

/*
static int	ft_exec_simple_command_parent(t_command *command, t_shell *data,
		t_exec_context *context, int pid, t_signal_child sig)
{
	if (!command || !data || !context || pid < 0)
		return (EXIT_FAILURE);
	if (context->input_fd != STDIN_FILENO)
		close(context->input_fd);
	if (context->output_fd != STDOUT_FILENO)
		close(context->output_fd);
	sigaction(SIGINT, &sig.sa_old_int, NULL);
	sigaction(SIGINT, &sig.sa_old_quit, NULL);
	if (context->pid_count < context->command_count)
	{
		context->pids[context->pid_count] = pid;
		context->pid_count++;
		context->last_pid = pid;
	}
	return (EXIT_SUCCESS);
}
*/

int	ft_exec_simple_command(t_command *command, t_shell *data,
		t_exec_context *context)
{
	pid_t			pid;
	int				exit_code;
	bool			is_parent_builtin;
	t_signal_child	sig;

	if (!command || !data || !context)
		return (EXIT_FAILURE);
	is_parent_builtin = ft_is_parent_builtin(command->name);
	if (is_parent_builtin && context->input_fd == STDIN_FILENO)
	{
		exit_code = ft_exec_parent_builtin(command, data);
		return (exit_code);
	}
	ft_set_signal_parent(&sig);
	// FORK
	pid = fork();
	if (pid < 0)
	{
		if (context->input_fd != STDIN_FILENO)
			close(context->input_fd);
		ft_printf(STDERR_FILENO, "minishell: error: failed to fork - %s\n",
			strerror(errno));
		return (EXIT_FAILURE);
	}
	if (pid == 0)
		ft_exec_simple_command_child(command, data, context, true);
	return (ft_exec_simple_command_parent(command, context, pid, sig));
}
