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
	int				exit_status;

	if (!data || !data->context)
		return (close(fd), false);
	context = data->context;
	if (WIFEXITED(context->last_exit_code))
	{
		exit_status = WEXITSTATUS(context->last_exit_code);
		if (exit_status == 130)
		{
			g_exit_code = 130;
			data->exit_code = 130;
		}
		else
			data->exit_code = exit_status;
	}
	else
		data->exit_code = EXIT_FAILURE;
	if (sigaction(SIGINT, &sig->sa_old_int, NULL) == -1)
		return (close(fd), ft_printf(STDERR_FILENO,
				"minishell: sigaction failed\n"), false);
	return (true);
}
