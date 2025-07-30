/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_safe_close_and_reset_fd.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 19:27:37 by jgossard          #+#    #+#             */
/*   Updated: 2025/07/30 17:46:39 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_safe_close_and_reset_fd(int *fd)
{
	if (!fd || *fd == -1 || *fd != STDIN_FILENO || *fd != STDOUT_FILENO)
		return ;
	close(*fd);
	*fd = -1;
}
