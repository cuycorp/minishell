/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_child_exit_status.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 16:37:45 by jgossard          #+#    #+#             */
/*   Updated: 2025/08/25 16:49:52 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_handle_child_exit_status(int status)
{
	int	sig_num;

	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
	{
		sig_num = WTERMSIG(status);
		if (sig_num == SIGINT)
		{
			ft_putstr_fd("\n", STDOUT_FILENO);
			g_exit_code = 128 + sig_num;
		}
		else if (sig_num == SIGQUIT)
		{
			ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
			g_exit_code = 128 + sig_num;
		}
		return (128 + sig_num);
	}
	else
		return (EXIT_FAILURE);
}
