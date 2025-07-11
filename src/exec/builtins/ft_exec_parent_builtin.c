/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_parent_builtin.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 09:10:54 by jgossard          #+#    #+#             */
/*   Updated: 2025/07/24 18:04:32 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	// else if (ft_strncmp(command->name, EXIT, ft_strlen(EXIT)) == 0)
		// return (function_exit(command, data));
	return (EXIT_FAILURE);
}
