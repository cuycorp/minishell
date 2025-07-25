/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_restore_signal_parent_n_exit_simple_co          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamaren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 13:09:56 by mcamaren          #+#    #+#             */
/*   Updated: 2025/08/01 13:09:58 by mcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_restore_signal_parent_n_exit_simple_command(t_signal_child *sig,
		t_exec_context *context)
{
	int	status;

	if (!context)
		return (false);
	status = context->last_exit_code;
	sigaction(SIGINT, &sig->sa_old_int, NULL);
	sigaction(SIGQUIT, &sig->sa_old_quit, NULL);
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT)
			ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
		if (WTERMSIG(status) == SIGINT)
			ft_putstr_fd("\n", STDERR_FILENO);
		context->last_exit_code = 128 + WTERMSIG(status);
		return (true);
	}
	return (false);
}
