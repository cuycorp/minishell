/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_simple_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 10:59:05 by jgossard          #+#    #+#             */
/*   Updated: 2025/08/20 14:53:45 by jgossard         ###   ########.fr       */
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
	ft_handle_dup2_and_close_fd(context->input_fd, STDIN_FILENO, data);
	ft_handle_dup2_and_close_fd(context->output_fd, STDOUT_FILENO, data);
	ft_close_heredocs_fd(data->ast_root);
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
	ft_reset_context_fds(data->context);
	// TODO: not usefull anymore to add pid to pids??
	if (context->pid_count < context->command_count)
	{
		context->pids[context->pid_count] = pid;
		context->pid_count++;
		context->last_pid = pid;
	}
	if (waitpid(pid, &context->last_exit_code, 0) == -1)
	{
		ft_error_failed_waitpid("ft_exec_simple_command_parent");
		return (EXIT_FAILURE);
	}
	ft_restore_signal_parent_simple_command(&sig, data);
	ft_mark_pids_reaped(context); // TODO: still usefull?
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
		return (ft_error_failed_to_fork("ft_exec_simple_comand"), EXIT_FAILURE);
	if (pid == 0)
	{
		if (!command->redirection)
			ft_close_heredocs_fd(data->ast_root);
		ft_exec_simple_command_child(command, data);
	}
	return (ft_exec_simple_command_parent(command, data, pid, sig));
}
