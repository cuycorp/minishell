/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_apply_dup2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 17:30:39 by jgossard          #+#    #+#             */
/*   Updated: 2025/08/20 16:23:59 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_apply_dup2(int oldfd, int newfd)
{
	if (oldfd < 0 || newfd < 0)
		return (false);
	if (dup2(oldfd, newfd) == -1)
	{
		ft_putstr_fd("Error: dup2 failed - ", STDERR_FILENO);
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		close(oldfd);
		return (false);
	}
	return (true);
}
