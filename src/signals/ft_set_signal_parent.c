/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_signal_parent.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamaren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 14:32:50 by mcamaren          #+#    #+#             */
/*   Updated: 2025/08/05 14:32:54 by mcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_set_signal_parent(t_signal_child *sig)
{
	if (!sig)
		return ;
	sig->sa_ignore.sa_handler = SIG_IGN;
	sigemptyset(&sig->sa_ignore.sa_mask);
	sig->sa_ignore.sa_flags = 0;
	if (sigaction(SIGINT, &sig->sa_ignore, &sig->sa_old_int) == -1)
		dprintf(STDERR_FILENO, "ft_set_signal_parent: Error with CTRL-C\n");
	//if (sigaction(SIGQUIT, &sig->sa_ignore, &sig->sa_old_quit) == -1)
	//	dprintf(STDERR_FILENO, "ft_set_signal_parent: Error with CTRL-slash \n");
}
