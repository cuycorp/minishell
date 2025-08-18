/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close_command_redirection_fds.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 17:28:16 by jgossard          #+#    #+#             */
/*   Updated: 2025/08/18 17:56:43 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_close_command_redirection_fds_thorough(t_command *command)
{
	t_redirection	*redir;
	int				fd;

	if (!command || !command->redirection)
		return;
	redir = command->redirection;
	while (redir)
	{
		if (redir->type == HEREDOC && redir->heredoc_fd != -1)
		{
			ft_safe_close_and_reset_fd(&redir->heredoc_fd);
		}
		else if (redir->type == REDIRECT_IN && redir->target)
		{
			// Check if file is currently open (this is just for testing)
			fd = open(redir->target, O_RDONLY);
			if (fd >= 0)
				close(fd); // This was just a test, close immediately
		}

		redir = redir->next;
	}
}
