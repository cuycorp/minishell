/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_exec_context.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 17:13:50 by jgossard          #+#    #+#             */
/*   Updated: 2025/08/05 11:26:51 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_exec_context(t_exec_context *context)
{
	if (!context)
		return ;
	if (context->pids)
	{
		free(context->pids);
		context->pids = NULL;
	}
	ft_safe_close_and_reset_fd(&context->input_fd); // TODO: do more test to check if it effectively closing fds
	ft_safe_close_and_reset_fd(&context->output_fd); // TODO: do more test to check if it effectively closing fds
	free(context);
}
