/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_external_command.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 16:00:15 by jgossard          #+#    #+#             */
/*   Updated: 2025/08/22 11:28:56 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exec_external_command(t_command *command, t_shell *data)
{
	char	*path;
	int		path_exit_code;

	if (!data || !command)
		return (EXIT_FAILURE);
	path_exit_code = 0;
	path = ft_get_command_path(command->name, data->ev, &data->error_message,
		&path_exit_code);
	if (!path)
	{
		ft_error_command_not_found(command->name, data->exit_code,
			data->error_message);
		return (path_exit_code);
	}
	execve(path, command->args, data->ev);
	ft_printf(STDERR_FILENO, "Error: execve failed: %s - %s\n", command->name,
		strerror(errno));
	free(path);
	return (EXIT_FAILURE);
}
