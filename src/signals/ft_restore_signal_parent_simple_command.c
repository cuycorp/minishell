/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_restore_signal_parent_simple_command            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 14:44:19 by mcamaren          #+#    #+#             */
/*   Updated: 2025/08/05 16:50:45 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_restore_signal_parent_simple_command(t_signal_child *sig,
		t_shell *data)
{
	t_exec_context	*context;
	int				sig_num;

	if (!data || !data->context)
		return ;
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
		else if (sig_num == SIGQUIT)
		{
			ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
			g_exit_code = 128 + sig_num;
		}
	}
	else
		data->exit_code = EXIT_FAILURE;
	sigaction(SIGINT, &sig->sa_old_int, NULL);
}
