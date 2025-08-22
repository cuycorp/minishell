/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_command_path.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 14:48:01 by jgossard          #+#    #+#             */
/*   Updated: 2025/08/22 12:17:44 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Checks if the given command path is valid and executable.
 *
 * This function performs a series of checks on the provided command path:
 * - Verifies that the file exists using `stat()`.
 * - Determines if the path points to a directory.
 * - Checks if the file has execution permission.
 *
 * If any check fails, it sets an appropriate error message and returns
 * the corresponding exit code:
 * - `EXIT_COMMAND_NOT_FOUND` (127) if the file does not exist.
 * - `EXIT_CANNOT_EXECUTE` (126) if the file is a directory or is not executable
 *
 * @param command The command path to validate (e.g., "./script.sh", "/bin/ls").
 * @param error_message A pointer to a string where the error message will be
 *                      stored on failure. Caller is responsible for freeing it.
 *
 * @return int Exit code:
 *         - `EXIT_SUCCESS` (0) if the path is valid and executable.
 *         - `EXIT_COMMAND_NOT_FOUND` (127) if the file does not exist.
 *         - `EXIT_CANNOT_EXECUTE` (126) if it's a directory or not executable.
 */
static int	ft_check_path_errors(char *command, char **error_message)
{
	struct stat	st;

	if (!command || !error_message)
		return (EXIT_COMMAND_NOT_FOUND);
	if (stat(command, &st) != 0)
	{
		*error_message = ft_strdup("No such file or directory");
		return (EXIT_COMMAND_NOT_FOUND);
	}
	if (S_ISDIR(st.st_mode))
	{
		*error_message = ft_strdup("Is a directory");
		return (EXIT_CANNOT_EXECUTE);
	}
	if (access(command, X_OK) != 0)
	{
		*error_message = ft_strdup("Permission denied");
		return (EXIT_CANNOT_EXECUTE);
	}
	return (EXIT_SUCCESS);
}

/**
 * @brief Handles command path resolution when command contains a slash
 * @param command The command with slash (relative/absolute path)
 * @param error_message Pointer to store error message
 * @param exit_code Pointer to store exit code
 * @return Duplicated command path on success, NULL on error
 */
static char	*ft_handle_path_command(char *command, char **error_message,
		int *exit_code)
{
	int	error_code;

	if (!command || !*command || !error_message || !exit_code)
		return (NULL);
	error_code = ft_check_path_errors(command, error_message);
	if (error_code != EXIT_SUCCESS)
	{
		*exit_code = error_code;
		return (NULL);
	}
	return (ft_strdup(command));
}

/**
 * @brief Resolves command path and handles all error cases
 *
 * This function handles two main scenarios:
 *
 * 1. Commands with slash (./cmd, /bin/cmd, ../cmd):
 *
 *    - Checks if path exists using stat()
 *
 *    - Returns EXIT_COMMAND_NOT_FOUND (127) if file doesn't exist
 *
 *    - Returns EXIT_CANNOT_EXECUTE (126) if it's a directory
 *
 *    - Returns EXIT_CANNOT_EXECUTE (126) if no execute permission
 *
 *    - Returns path if all checks pass
 *
 * 2. Commands without slash (ls, grep, hello):
 *
 *    - Searches in PATH directories using ft_search_in_paths()
 *
 *    - Returns EXIT_COMMAND_NOT_FOUND (127) if PATH is empty/invalid
 *
 *    - Returns EXIT_COMMAND_NOT_FOUND (127) if command not found in PATH
 *
 *    - Returns full path if command found and executable
 *
 * @param command Command name or path to resolve
 * @param envp Environment variables array (for PATH lookup)
 * @param error_message Pointer to store descriptive error message
 * @param exit_code Pointer to store appropriate shell exit code
 * @return Full path to executable on success, NULL on any error
 */
char	*ft_get_command_path(char *command, char **envp, char **error_message,
		int *exit_code)
{
	if (!command || !*command || !error_message)
		return (NULL);
	if (ft_strchr(command, SLASH_CHARACTER))
		return (ft_handle_path_command(command, error_message, exit_code));
	return (ft_handle_path_search(command, envp, error_message, exit_code));
}
