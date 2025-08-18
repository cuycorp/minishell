/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_failed_to_pipe.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 15:01:43 by jgossard          #+#    #+#             */
/*   Updated: 2025/08/18 15:03:48 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error_failed_to_pipe(char *scope)
{
	if (scope)
		ft_printf(STDERR_FILENO, "minishell: %s: pipe failed: %s\n",
			scope, strerror(errno));
	else
		ft_printf(STDERR_FILENO, "minishell: pipe failed: %s\n",
			strerror(errno));
}
