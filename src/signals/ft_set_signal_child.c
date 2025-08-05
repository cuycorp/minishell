/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_signal_child.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 14:38:31 by mcamaren          #+#    #+#             */
/*   Updated: 2025/08/05 16:50:37 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_set_signal_child(bool is_simple_command)
{
	struct sigaction	sig_child;

	(void)is_simple_command;
	sig_child.sa_handler = SIG_DFL;
	sigemptyset(&sig_child.sa_mask);
	sig_child.sa_flags = 0;
	sigaction(SIGINT, &sig_child, NULL);
	// if (is_simple_command == true)
	///	sigaction(SIGQUIT, &sig_child, NULL);
}
