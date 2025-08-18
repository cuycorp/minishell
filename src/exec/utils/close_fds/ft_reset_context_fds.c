/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reset_context_fds.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 19:01:15 by jgossard          #+#    #+#             */
/*   Updated: 2025/08/14 19:01:31 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_reset_context_fds(t_exec_context *context)
{
	if (!context)
		return;
	if (context->input_fd != STDIN_FILENO)
		ft_safe_close_and_reset_fd(&context->input_fd);
	if (context->output_fd != STDOUT_FILENO)
		ft_safe_close_and_reset_fd(&context->output_fd);
	context->input_fd = STDIN_FILENO;
	context->output_fd = STDOUT_FILENO;
}
