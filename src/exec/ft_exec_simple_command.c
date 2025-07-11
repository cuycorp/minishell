/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_simple_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 10:59:05 by jgossard          #+#    #+#             */
/*   Updated: 2025/07/28 12:00:23 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exec_simple_command(t_command *command, t_shell *data, int input_fd, int *last_pid)
{
	pid_t	pid;
	int		exit_code;
	bool	is_parent_builtin;

	if (!command || !data || !last_pid || input_fd < 0) // TODO: add check on input_fd
		return (EXIT_FAILURE);
	is_parent_builtin = ft_is_parent_builtins(command->name);
	if (is_parent_builtin && input_fd == STDIN_FILENO)
	{
		exit_code = ft_exec_parent_builtin(command, data);
		*last_pid = -1;
		return (exit_code);
	}
	// FORK
	pid = fork();
	if (pid < 0)
	{
		if (input_fd != STDIN_FILENO)
			close(input_fd);
		return (perror("failed to fork"), EXIT_FAILURE);
	}
	if (pid == 0)
	{
		// Apply input_fd redirection from pipe
		if (input_fd != STDIN_FILENO)
		{
			if (!ft_apply_dup2(input_fd, STDIN_FILENO))
				exit(EXIT_FAILURE);
			close(input_fd);
		}
		// Apply redirections
		if (command->redirection && !ft_prepare_command_io(command->redirection))
			exit(EXIT_FAILURE);
		if (ft_is_builtin_function(command->name))
			exit_code = ft_exec_builtin(command, data);
		else
			exit_code = ft_exec_command(command, data);
		exit(exit_code);
	}
	if (input_fd != STDIN_FILENO)
		close(input_fd);
	if (data->pid_count < data->command_count)
	{
		data->pids[data->pid_count] = pid;
		data->pid_count++;
		*last_pid = pid;
	}
	return (EXIT_SUCCESS);
}
