/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close_context_fds_before_fork.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 16:24:19 by jgossard          #+#    #+#             */
/*   Updated: 2025/08/18 17:09:55 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_close_context_fds_before_fork(t_exec_context *context)
{
	if (!context)
		return ;
	if (context->input_fd > STDERR_FILENO)
		ft_safe_close_and_reset_fd(&context->input_fd);
	if (context->output_fd > STDERR_FILENO)
		ft_safe_close_and_reset_fd(&context->output_fd);
}
