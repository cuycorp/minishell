/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 10:31:20 by jgossard          #+#    #+#             */
/*   Updated: 2025/07/24 17:50:21 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Checks if a given command name is a shell builtin command.
 *
 * This function compares the input command name against a list of known
 * builtin shell commands (e.g., echo, cd, pwd, export, unset, env, exit).
 * It returns true if the command matches any of the builtin commands exactly.
 *
 * @param command_name The command name to check (e.g., "echo", "cd").
 * @return true if the command is a builtin; false otherwise.
 *
 * @note	This function assumes that the builtin command names are defined
 *			as constants (e.g., ECHO, CD, etc.), and that command_name is a
 *			null-terminated string.
 */
bool	ft_is_builtin_function(char *command_name)
{
	if (!command_name)
		return (false);
	return (ft_strncmp(command_name, ECHO_BUILTIN, ft_strlen(ECHO_BUILTIN)) == 0
		|| ft_strncmp(command_name, CD, ft_strlen(CD)) == 0
		|| ft_strncmp(command_name, PWD, ft_strlen(PWD)) == 0
		|| ft_strncmp(command_name, EXPORT, ft_strlen(EXPORT)) == 0
		|| ft_strncmp(command_name, UNSET, ft_strlen(UNSET)) == 0
		|| ft_strncmp(command_name, ENV, ft_strlen(ENV)) == 0
		|| ft_strncmp(command_name, EXIT, ft_strlen(EXIT)) == 0);
}
