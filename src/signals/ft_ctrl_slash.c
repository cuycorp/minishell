/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ctrl_slash.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamaren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 17:49:12 by mcamaren          #+#    #+#             */
/*   Updated: 2025/07/24 17:49:16 by mcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_ctrl_slash(void)
{
	struct sigaction sa;

	sa.sa_handler = SIG_IGN;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGQUIT, &sa, NULL);
}

/*
	sa.sa_handler = SIG_IGN; // Ignore the SIGQUIT signal
	sa.sa_flags = SA_RESTART; // Ensure interrupted system calls are restarted
	sigemptyset(&sa.sa_mask); // No other signals blocked during handler
	sigaction(SIGQUIT, &sa, NULL); // Set the handler for SIGQUIT
*/

