/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_parent_builtin.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 09:10:54 by jgossard          #+#    #+#             */
/*   Updated: 2025/08/20 15:55:12 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Checks if a given command is a shell builtin that must be executed in
 * the parent process.
 *
 * This function determines whether the provided command name corresponds to one
 * of the built-in commands (`cd`, `export`, `unset`, `exit`) that require
 * execution in the parent process of the minishell.
 *
 * @param command_name The name of the command to check.
 * @return true if the command is a parent process builtin; false otherwise or
 * if command_name is NULL.
 */
int	ft_exec_parent_builtin(t_command *command, t_shell *data)
{
	if (!command || !data)
		return (EXIT_FAILURE);
	if (ft_strncmp(command->name, CD, ft_strlen(CD)) == 0)
		return (function_cd(&data, command));
	else if (ft_strncmp(command->name, EXPORT, ft_strlen(EXPORT)) == 0)
		return (function_export(command, data));
	else if (ft_strncmp(command->name, UNSET, ft_strlen(UNSET)) == 0)
		return (function_unset(command, data));
	else if (ft_strncmp(command->name, EXIT, ft_strlen(EXIT)) == 0)
		return (function_exit(command, data));
	return (EXIT_FAILURE);
}
