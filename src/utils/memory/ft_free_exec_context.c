/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_exec_context.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 17:13:50 by jgossard          #+#    #+#             */
/*   Updated: 2025/07/30 08:58:54 by jgossard         ###   ########.fr       */
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
	if (context->input_fd != STDIN_FILENO && context->input_fd != -1)
	{
		close(context->input_fd);
		context->input_fd = STDIN_FILENO;
	}
	if (context->output_fd != STDOUT_FILENO && context->output_fd != -1)
	{
		close(context->output_fd);
		context->output_fd = STDOUT_FILENO;
	}
	free(context);
}
