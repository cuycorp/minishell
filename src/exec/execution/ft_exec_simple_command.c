/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_simple_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 10:59:05 by jgossard          #+#    #+#             */
/*   Updated: 2025/08/05 16:52:16 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_exec_simple_command_child(t_command *command, t_shell *data)
{
	t_exec_context	*context;
	int				exit_code;

	if (!command || !data || !data->context)
		ft_exit_child(data, EXIT_FAILURE);
	ft_set_signal_child(true);
	context = data->context;
	// Prepare redirection
	if (!ft_prepare_command_io(command->redirection, context))
		ft_exit_child(data, EXIT_FAILURE);
	// Apply pipe or redirection fds
	if (context->input_fd != STDIN_FILENO)
	{
		if (!ft_apply_dup2(context->input_fd, STDIN_FILENO))
			ft_exit_child(data, EXIT_FAILURE);
		close(context->input_fd);
	}
	if (context->output_fd != STDOUT_FILENO)
	{
		if (!ft_apply_dup2(context->output_fd, STDOUT_FILENO))
			ft_exit_child(data, EXIT_FAILURE);
		close(context->output_fd);
	}
	// TODO: fix issue with exit_code here
	if (ft_is_child_builtin(command->name))
		exit_code = ft_exec_child_builtin(command, data);
	else
		exit_code = ft_exec_external_command(command, data);
	ft_exit_child(data, exit_code);
}

static int	ft_exec_simple_command_parent(t_command *command, t_shell *data,
		int pid, t_signal_child sig)
{
	t_exec_context	*context;

	if (!command || !data || !data->context || pid < 0)
		return (EXIT_FAILURE);
	context = data->context;
	if (context->input_fd != STDIN_FILENO)
		close(context->input_fd);
	if (context->output_fd != STDOUT_FILENO)
		close(context->output_fd);
	if (context->pid_count < context->command_count)
	{
		context->pids[context->pid_count] = pid;
		context->pid_count++;
		context->last_pid = pid;
	}
	if (waitpid(pid, &context->last_exit_code, 0) == -1)
	{
		dprintf(STDERR_FILENO, "minishell: waitpid failed\n");
		return (EXIT_FAILURE);
	}
	ft_restore_signal_parent_simple_command(&sig, data);
	ft_mark_pids_reaped(context);
	return (EXIT_SUCCESS);
}

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
	{
		ft_printf(STDERR_FILENO, "minishell: error: failed to fork - %s\n",
			strerror(errno));
		return (EXIT_FAILURE);
	}
	if (pid == 0)
		ft_exec_simple_command_child(command, data);
	return (ft_exec_simple_command_parent(command, data, pid, sig));
}
