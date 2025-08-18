/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prepare_command_input.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 15:43:31 by jgossard          #+#    #+#             */
/*   Updated: 2025/08/18 16:51:15 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	ft_handle_heredoc_input(t_redirection *redirection,
		t_redirection *last_input, t_exec_context *context)
{
	if (redirection != last_input)
	{
		ft_safe_close_and_reset_fd(&redirection->heredoc_fd);
		return (true);
	}
	ft_safe_close_and_reset_fd(&context->input_fd);
	context->input_fd = redirection->heredoc_fd;
	redirection->heredoc_fd = -1;
	return (true);
}

static bool	ft_handle_file_input(t_redirection *redirection,
		t_redirection *last_input, t_exec_context *context)
{
	int	fd;

	fd = open(redirection->target, O_RDONLY);
	if (fd < 0)
	{
		ft_printf(STDERR_FILENO, "minishell: %s: %s\n", redirection->target,
			strerror(errno));
		return (false);
	}
	if (redirection == last_input)
	{
		ft_safe_close_and_reset_fd(&context->input_fd);
		context->input_fd = fd;
	}
	else
		close(fd);
	return (true);
}

bool	ft_prepare_command_inputs(t_redirection *redirection,
		t_redirection *last_input, t_exec_context *context)
{
	if (!redirection || !context)
		return (false);
	if (redirection->type == HEREDOC)
		return (ft_handle_heredoc_input(redirection, last_input, context));
	else if (redirection->type == REDIRECT_IN)
		return (ft_handle_file_input(redirection, last_input, context));
	return (true);
}
