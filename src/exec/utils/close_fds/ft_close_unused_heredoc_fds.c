/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close_unused_heredoc_fds.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 15:29:48 by jgossard          #+#    #+#             */
/*   Updated: 2025/08/18 16:58:19 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_close_unused_heredocs(t_redirection *redirections,
		t_redirection *last_input)
{
	if (!redirections || !last_input)
		return ;
	while (redirections)
	{
		if (redirections->type == HEREDOC && redirections != last_input
			&& redirections->heredoc_fd != -1)
		{
			ft_safe_close_and_reset_fd(&redirections->heredoc_fd);
		}
		redirections = redirections->next;
	}
}
