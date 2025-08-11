/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_external_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 16:00:15 by jgossard          #+#    #+#             */
/*   Updated: 2025/07/29 22:24:31 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_get_command_path(char *command, char **envp)
{
	char	**paths;
	char	*directory_path;
	char	*command_path;
	int		paths_len;
	int		i;

	if (!command)
		return (NULL);
	// Check if already an absolute or relative path
	if (ft_strchr(command, SLASH_CHARACTER))
	{
		if (access(command, X_OK) == 0)
			return (ft_strdup(command));
		return (NULL);
	}
	// Build command path
	paths = ft_split_env_value(PATH, envp);
	if (!paths)
		return (NULL);
	paths_len = ft_strarr_len(paths);
	i = 0;
	while (i < paths_len)
	{
		directory_path = ft_strjoin(paths[i], SLASH_STRING);
		if (!directory_path)
			return (ft_free_char_tab(paths), NULL);
		command_path = ft_strjoin(directory_path, command);
		if (!command_path)
			return (ft_free_char_tab(paths), free(directory_path), NULL);
		if (access(command_path, F_OK | X_OK) == 0)
			return (ft_free_char_tab(paths), free(directory_path), command_path);
		free(directory_path);
		free(command_path);
		i++;
	}
	ft_free_char_tab(paths);
	return (NULL);
}


int	ft_exec_external_command(t_command *command, t_shell *data)
{
	char	*path;

	if (!data || !command)
		return (EXIT_FAILURE);
	path = ft_get_command_path(command->name, data->ev);
	if (!path)
	{
		ft_error_command_not_found(command->name);
		return (EXIT_COMMAND_NOT_FOUND); // TODO: check if it is the correct exit code
	}
	command->args = ft_expand_arguments_with_wildcards(command->args);
	if (!command->args)
	{
		ft_printf(STDERR_FILENO, "minishell: errors occured during wildcardexpansion \n");
		return (EXIT_FAILURE);
	}
	execve(path, command->args, data->ev);
	ft_printf(STDERR_FILENO, "Error: %s - %s\n", command->name, strerror(errno));
	free(path);
	return (EXIT_FAILURE);
}
