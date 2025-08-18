/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_failed_waitpid.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 13:57:49 by jgossard          #+#    #+#             */
/*   Updated: 2025/08/18 15:03:54 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error_failed_waitpid(char *scope)
{
	if (scope)
		ft_printf(STDERR_FILENO, "minishell: %s: waitpid failed: %s\n",
			scope, strerror(errno));
	else
		ft_printf(STDERR_FILENO, "minishell: waitpid failed: %s\n",
			strerror(errno));
}
