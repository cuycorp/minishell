/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close_fds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 14:48:09 by jgossard          #+#    #+#             */
/*   Updated: 2025/08/04 11:30:41 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_close_fds(int *pipe_fd)
{
	if (!pipe_fd)
		return ;
	close(pipe_fd[READ_END]);
	close(pipe_fd[WRITE_END]);
}
