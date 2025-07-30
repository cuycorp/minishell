/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_command_not_found.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 10:41:13 by jgossard          #+#    #+#             */
/*   Updated: 2025/07/30 10:41:15 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error_command_not_found(char *command_name)
{
	ft_printf(STDERR_FILENO, "Minishell: %s : command not found\n", command_name);
}
