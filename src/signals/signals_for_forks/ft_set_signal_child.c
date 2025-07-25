/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_signal_child.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamaren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 12:22:06 by mcamaren          #+#    #+#             */
/*   Updated: 2025/08/01 12:22:09 by mcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_set_signal_child(bool simple_command)
{
	struct sigaction	sig_child;

	sig_child.sa_handler = SIG_DFL;
	sigemptyset(&sig_child.sa_mask);
	sig_child.sa_flags = 0;
	sigaction(SIGINT, &sig_child, NULL);
	if (simple_command == true)
		sigaction(SIGQUIT, &sig_child, NULL);
}
