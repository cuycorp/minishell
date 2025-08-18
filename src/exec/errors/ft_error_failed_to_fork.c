/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_failed_to_fork.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 13:55:24 by jgossard          #+#    #+#             */
/*   Updated: 2025/08/18 15:03:59 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error_failed_to_fork(char *scope)
{
	if (scope)
		ft_printf(STDERR_FILENO, "minishell: %s: failed to fork - %s\n",
			scope, strerror(errno));
	else
		ft_printf(STDERR_FILENO, "minishell: error: failed to fork - %s\n",
		strerror(errno));
}
