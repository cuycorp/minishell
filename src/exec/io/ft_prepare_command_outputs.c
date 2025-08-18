/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prepare_command_outputs.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 15:40:11 by jgossard          #+#    #+#             */
/*   Updated: 2025/08/18 15:42:32 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_open_output_file(t_redirection *redirection)
{
	int	fd;

	if (redirection->type == REDIRECT_OUT)
	{
		fd = open(redirection->target, O_WRONLY | O_CREAT | O_TRUNC,
				STANDARD_FILE_PERMISSIONS);
	}
	else if (redirection->type == APPEND_OUT)
	{
		fd = open(redirection->target, O_WRONLY | O_CREAT | O_APPEND,
				STANDARD_FILE_PERMISSIONS);
	}
	else
		return (-1);
	return (fd);
}

bool	ft_prepare_command_outputs(t_redirection *redirection,
		t_redirection *last_output, t_exec_context *context)
{
	int	fd;

	if (!redirection || !context)
		return (false);
	fd = ft_open_output_file(redirection);
	if (fd < 0)
	{
		ft_printf(STDERR_FILENO, "minishell: %s: %s\n",
			redirection->target, strerror(errno));
		return (false);
	}
	if (redirection == last_output)
	{
		if (context->output_fd != STDOUT_FILENO)
			ft_safe_close_and_reset_fd(&context->output_fd);
		context->output_fd = fd;
	}
	else
		close(fd);
	return (true);
}
