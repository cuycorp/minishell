/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prepare_command_io.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 11:33:11 by jgossard          #+#    #+#             */
/*   Updated: 2025/07/30 09:16:42 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	ft_get_last_io_redirection(
	t_redirection *redirection, t_redirection **last_input,
	t_redirection **last_output)
{
	if (!redirection || !last_input || !last_output)
		return (false);
	while (redirection)
	{
		if (redirection->type == HEREDOC || redirection->type == REDIRECT_IN)
			*last_input = redirection;
		else if (redirection->type == REDIRECT_OUT
			|| redirection->type == APPEND_OUT)
			*last_output = redirection;
		redirection = redirection->next;
	}
	return (true);
}

static bool	ft_prepare_command_inputs(t_redirection *redirection,
		t_redirection *last_input, t_exec_context *context)
{
	int	fd;

	if (!redirection || !context)
		return (false);
	if (redirection->type == HEREDOC && redirection == last_input)
	{
		ft_safe_close_and_reset_fd(&context->input_fd);
		context->input_fd = redirection->heredoc_fd;
	}
	else if (redirection->type == REDIRECT_IN)
	{
		fd = open(redirection->target, O_RDONLY);
		if (fd < 0)
			return (ft_printf(STDERR_FILENO, "minishell: %s: %s\n",
					redirection->target, strerror(errno)), false);
		if (redirection == last_input)
		{
			ft_safe_close_and_reset_fd(&context->input_fd);
			context->input_fd = fd;
		}
		else
			close(fd);
	}
	return (true);
}

static bool	ft_prepare_command_outputs(t_redirection *redirection,
		t_redirection *last_output, t_exec_context *context)
{
	int	fd;

	if (!redirection || !context)
		return (false);
	if (redirection->type == REDIRECT_OUT)
		fd = open(redirection->target, O_WRONLY | O_CREAT | O_TRUNC,
				STANDARD_FILE_PERMISSIONS);
	else if (redirection->type == APPEND_OUT)
		fd = open(redirection->target, O_WRONLY | O_CREAT | O_APPEND,
				STANDARD_FILE_PERMISSIONS);
	else
		return (false);
	if (fd < 0)
		return (ft_printf(STDERR_FILENO, "minishell: %s: %s\n",
				redirection->target, strerror(errno)), false);
	if (redirection == last_output)
	{
		ft_safe_close_and_reset_fd(&context->output_fd);
		context->output_fd = fd;
	}
	else
		close(fd);
	return (true);
}

static bool	ft_prepare_command_redirection(t_redirection *redirection,
		t_redirection *last_input, t_redirection *last_output,
		t_exec_context *context)
{
	if (!redirection || !context)
		return (false);
	while (redirection)
	{
		if (redirection->type == HEREDOC || redirection->type == REDIRECT_IN)
		{
			if (!ft_prepare_command_inputs(redirection, last_input, context))
				return (false);
		}
		else if (redirection->type == REDIRECT_OUT
			|| redirection->type == APPEND_OUT)
		{
			if (!ft_prepare_command_outputs(redirection, last_output, context))
				return (false);
		}
		redirection = redirection->next;
	}
	return (true);
}

bool	ft_prepare_command_io(t_redirection *redirection,
		t_exec_context *context)
{
	t_redirection	*last_input;
	t_redirection	*last_output;

	if (!context)
		return (false);
	if (!redirection)
		return (true);
	last_input = NULL;
	last_output = NULL;
	if (!ft_get_last_io_redirection(redirection, &last_input, &last_output))
		return (false);
	return (ft_prepare_command_redirection(redirection, last_input, last_output,
			context));
}
