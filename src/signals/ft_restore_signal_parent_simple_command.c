/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_restore_signal_parent_simple_command.c          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 14:44:19 by mcamaren          #+#    #+#             */
/*   Updated: 2025/08/25 16:53:09 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_restore_signal_parent_simple_command(t_signal_child *sig,
		t_shell *data)
{
	t_exec_context	*context;
	int				result;

	if (!data || !data->context)
		return ;
	context = data->context;
	result = ft_handle_child_exit_status(context->last_exit_code);
	data->exit_code = result;
	sigaction(SIGINT, &sig->sa_old_int, NULL);
}
