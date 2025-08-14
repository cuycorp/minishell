/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ctrl_c.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamaren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 11:45:02 by mcamaren          #+#    #+#             */
/*   Updated: 2025/08/05 11:45:05 by mcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_handle_ctrl_c(int sig)
{
	if (sig == SIGINT)
	{
		g_exit_code = 128 + sig;
		rl_replace_line("", 0);
		rl_on_new_line();
		ft_printf(STDOUT_FILENO, "\n");
		rl_redisplay();
	}
}

void	ft_ctrl_c(void)
{
	struct sigaction	sa;

	sa.sa_handler = &ft_handle_ctrl_c;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGINT, &sa, NULL) == -1)
		dprintf(STDERR_FILENO, " Error with CTRL-C\n");
}
