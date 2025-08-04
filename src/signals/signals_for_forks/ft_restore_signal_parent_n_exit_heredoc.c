/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_restore_signal_parent_n_exit_heredoc.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamaren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 12:43:55 by mcamaren          #+#    #+#             */
/*   Updated: 2025/07/31 12:43:59 by mcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// bool ft_ctrl_c_restore_signal_parent_n_exit(t_signal_child *sig, int status, int pipe_fd[2])
bool ft_restore_signal_parent_n_exit_heredoc(t_signal_child *sig, int status, int fd, t_exec_context *context)
{
	if (!context)
		return (false);
	dprintf(STDERR_FILENO, "ft_restore_signal_parent_n_exit_heredoc: in function\n");

	if (sigaction(SIGINT, &sig->sa_old_int, NULL) == -1)
	{
		close(fd);
		return (false);
	}
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		ft_printf(STDERR_FILENO, "in SIGINT %d\n", status); //debug line
		ft_putstr_fd("\n", STDERR_FILENO);
		context->last_exit_code =  status;
		//context->last_exit_code = 128 + WTERMSIG(status);
		// return (true);
	}
	dprintf(STDERR_FILENO, "ft_restore_signal_parent_n_exit_heredoc: end function\n");
	return (true);
}
