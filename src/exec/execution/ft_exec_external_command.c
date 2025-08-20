/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_external_command.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 16:00:15 by jgossard          #+#    #+#             */
/*   Updated: 2025/08/20 16:22:02 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exec_external_command(t_command *command, t_shell *data)
{
	char	*path;

	if (!data || !command)
		return (EXIT_FAILURE);
	path = ft_get_command_path(command->name, data->ev, &data->error_message);
	if (!path)
	{
		ft_error_command_not_found(command->name, data->exit_code);
		return (EXIT_COMMAND_NOT_FOUND);
	}
	execve(path, command->args, data->ev);
	ft_printf(STDERR_FILENO, "Error:%s - %s\n", command->name, strerror(errno));
	free(path);
	return (EXIT_FAILURE);
}
