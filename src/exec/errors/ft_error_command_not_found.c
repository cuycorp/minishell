/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_command_not_found.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 10:41:13 by jgossard          #+#    #+#             */
/*   Updated: 2025/08/21 10:44:06 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error_command_not_found(char *command_name, int exit_code,
		char *error_message)
{
	if (error_message && command_name)
		ft_printf(STDERR_FILENO, "Minishell: %s: %s\n", command_name,
			error_message);
	else if (!command_name)
		ft_printf(STDERR_FILENO, "Minishell: %d: command not found\n",
			exit_code);
	else
		ft_printf(STDERR_FILENO, "Minishell: %s: command not found\n",
			command_name);
}
