/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_safe_close_and_reset_fd.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 19:27:37 by jgossard          #+#    #+#             */
/*   Updated: 2025/08/20 16:28:09 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_safe_close_and_reset_fd(int *fd)
{
	if (!fd || *fd == -1)
		return ;
	if (*fd == STDIN_FILENO || *fd == STDOUT_FILENO || *fd == STDERR_FILENO)
		return ;
	if (close(*fd) == -1)
	{
		ft_printf(STDERR_FILENO, "minishell: failed to close fd %d: %s\n",
			*fd, strerror(errno));
	}
	*fd = -1;
}
