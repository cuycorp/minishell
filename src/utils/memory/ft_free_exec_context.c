/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_exec_context.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 17:13:50 by jgossard          #+#    #+#             */
/*   Updated: 2025/07/28 20:41:50 by jgossard         ###   ########.fr       */
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
	if (context->input_fd > 2)
		close(context->input_fd);
	if (context->output_fd > 2)
		close(context->output_fd);
	free(context);
}
