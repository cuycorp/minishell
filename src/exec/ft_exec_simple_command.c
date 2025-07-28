/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_simple_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 10:59:05 by jgossard          #+#    #+#             */
/*   Updated: 2025/07/28 19:57:13 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_exec_simple_command_child(t_command *command, t_shell *data,
		t_exec_context *context)
{
	int	exit_code;

	if (!command || !data || !context)
		exit(EXIT_FAILURE);
	// Prepare redirection
	if (!ft_prepare_command_io(command->redirection, context))
		exit(EXIT_FAILURE);
	// Apply pipe or redirection fdss
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
	if (ft_is_builtin_function(command->name))
		exit_code = ft_exec_child_builtin(command, data);
	else
		exit_code = ft_exec_command(command, data);
	exit(exit_code);
}

static int	ft_exec_simple_command_parent(t_command *command, t_shell *data,
		t_exec_context *context, int pid)
{
	if (!command || !data || !context || pid < 0)
		return (EXIT_FAILURE);
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
	return (EXIT_SUCCESS);
}

int	ft_exec_simple_command(t_command *command, t_shell *data,
		t_exec_context *context)
{
	pid_t	pid;
	int		exit_code;
	bool	is_parent_builtin;

	if (!command || !data || !context)
		return (EXIT_FAILURE);
	is_parent_builtin = ft_is_parent_builtins(command->name);
	if (is_parent_builtin && context->input_fd == STDIN_FILENO)
	{
		exit_code = ft_exec_parent_builtin(command, data);
		// context->last_pid = -1; // TODO: not sure? to keep?
		return (exit_code);
	}
	// FORK
	pid = fork();
	if (pid < 0)
	{
		if (context->input_fd != STDIN_FILENO)
			close(context->input_fd);
		return (perror("failed to fork"), EXIT_FAILURE);
	}
	if (pid == 0)
		ft_exec_simple_command_child(command, data, context);
	return (ft_exec_simple_command_parent(command, data, context, pid));
}
