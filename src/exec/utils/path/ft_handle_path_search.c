/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_path_search.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 11:49:30 by jgossard          #+#    #+#             */
/*   Updated: 2025/08/22 12:42:24 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_build_full_path(char *directory, char *command)
{
	char	*full_path;
	char	*directory_with_slash;

	if (!directory || !command)
		return (NULL);
	directory_with_slash = ft_strjoin(directory, SLASH_STRING);
	if (!directory_with_slash)
		return (NULL);
	full_path = ft_strjoin(directory_with_slash, command);
	if (!full_path)
	{
		free(directory_with_slash);
		return (NULL);
	}
	free(directory_with_slash);
	return (full_path);
}

static char	*ft_search_in_paths(char *command, char **paths)
{
	int		i;
	char	*command_path;

	if (!command || !paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		command_path = ft_build_full_path(paths[i], command);
		if (!command_path)
			return (ft_free_char_tab(paths), NULL);
		if (access(command_path, F_OK | X_OK) == 0)
			return (ft_free_char_tab(paths), command_path);
		free(command_path);
		i++;
	}
	return (NULL);
}

/**
 * @brief Handles command search in PATH directories
 * @param command The command name to search for
 * @param envp Environment variables array
 * @param error_message Pointer to store error message
 * @param exit_code Pointer to store exit code
 * @return Full path to command on success, NULL on error
 */
char	*ft_handle_path_search(char *command, char **envp, char **error_message,
		int *exit_code)
{
	char	**paths;
	char	*result;

	if (!command || !*command || !envp || !error_message || !exit_code)
		return (NULL);
	paths = ft_split_env_value(PATH, envp);
	if (!paths)
	{
		*error_message = ft_strdup("No such file or directory");
		*exit_code = EXIT_COMMAND_NOT_FOUND;
		return (NULL);
	}
	result = ft_search_in_paths(command, paths);
	if (!result)
	{
		ft_free_char_tab(paths);
		*error_message = ft_strdup("command not found");
		*exit_code = EXIT_COMMAND_NOT_FOUND;
		return (NULL);
	}
	return (result);
}
