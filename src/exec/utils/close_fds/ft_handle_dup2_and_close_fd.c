/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_dup2_and_close_fd.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 13:23:26 by jgossard          #+#    #+#             */
/*   Updated: 2025/08/18 17:09:37 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_handle_dup2_and_close_fd(int oldfd, int newfd, t_shell *data)
{
	if (!data)
		return ;
	if (oldfd != newfd)
	{
		if (!ft_apply_dup2(oldfd, newfd))
			ft_exit_child(data, EXIT_FAILURE);
		close(oldfd);
	}
}
