/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_command_path.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 14:48:01 by jgossard          #+#    #+#             */
/*   Updated: 2025/08/19 10:07:08 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_build_full_path(char *directory, char *command)
{
	char	*full_path;
	char	*directory_with_slash;

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

char	*ft_get_command_path(char *command, char **envp, char **error_message)
{
	char	**paths;
	char	*result;

	if (!command || !error_message)
		return (NULL);
	if (ft_strchr(command, SLASH_CHARACTER))
	{
		if (access(command, X_OK) == 0)
			return (ft_strdup(command));
		dprintf(STDERR_FILENO, "access failed\n");
		return (NULL);
	}
	paths = ft_split_env_value(PATH, envp);
	if (!paths)
	{
		*error_message = ft_strdup("No such file or directory");
		return (NULL);
	}
	result = ft_search_in_paths(command, paths);
	if (!result)
		ft_free_char_tab(paths);
	return (result);
}
