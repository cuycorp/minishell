/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close_pipe_fds.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 14:48:09 by jgossard          #+#    #+#             */
/*   Updated: 2025/08/18 13:51:22 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_close_pipe_fds(int *pipe_fd)
{
	if (!pipe_fd)
		return ;
	close(pipe_fd[READ_END]);
	close(pipe_fd[WRITE_END]);
}
