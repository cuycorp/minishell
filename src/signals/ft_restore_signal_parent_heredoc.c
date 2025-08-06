/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_restore_signal_parent_heredoc        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 14:44:19 by mcamaren          #+#    #+#             */
/*   Updated: 2025/08/05 16:50:45 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_restore_signal_parent_heredoc(t_signal_child *sig, t_shell *data,
		int fd)
{
	t_exec_context	*context;
	int				sig_num;

	if (!data || !data->context)
		return (close(fd), false);
	context = data->context;
	if (WIFEXITED(context->last_exit_code))
		data->exit_code = WEXITSTATUS(context->last_exit_code);
	else if (WIFSIGNALED(context->last_exit_code))
	{
		sig_num = WTERMSIG(context->last_exit_code);
		if (sig_num == SIGINT)
		{
			g_exit_code = 128 + sig_num;
			ft_putstr_fd("\n", STDOUT_FILENO);
		}
	}
	else
		data->exit_code = EXIT_FAILURE;
	if (sigaction(SIGINT, &sig->sa_old_int, NULL) == -1)
		return (close(fd), ft_printf(STDERR_FILENO,
				"minishell: sigaction failed\n"), false);
	return (true);
}
