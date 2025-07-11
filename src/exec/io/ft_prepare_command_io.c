/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prepare_command_io.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 11:33:11 by jgossard          #+#    #+#             */
/*   Updated: 2025/07/28 12:20:07 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_redirection	*ft_get_last_input_redirection(t_redirection *redirection)
{
	t_redirection	*last_input;

	if (!redirection)
		return (NULL);
	last_input = NULL;
	while (redirection)
	{
		if (redirection->type == HEREDOC || redirection->type == REDIRECT_IN)
			last_input = redirection;
		redirection = redirection->next;
	}
	return (last_input);
}

static bool	ft_prepare_command_inputs(t_redirection *redirection,
		t_redirection *last_input, int *input_fd)
{
	int	fd;

	if (!redirection || !last_input || !input_fd)
		return (false);
	if (redirection->type == HEREDOC)
	{
		if (redirection->heredoc_fd == -1)
			return (false);
		if (redirection == last_input)
			*input_fd = redirection->heredoc_fd;
		else
			close(redirection->heredoc_fd);
	}
	else if (redirection->type == REDIRECT_IN)
	{
		fd = open(redirection->target, O_RDONLY);
		if (fd < 0)
			return (ft_printf(STDERR_FILENO, "minishell: %s: %s\n",
					redirection->target, strerror(errno)), false);
		if (redirection == last_input)
			*input_fd = fd;
		else
			close(fd);
	}
	return (true);
}

static bool	ft_prepare_command_outputs(t_redirection *redirection,
		int *output_fd)
{
	if (!redirection || !output_fd)
		return (false);
	if (redirection->type == REDIRECT_OUT)
	{
		*output_fd = open(redirection->target, O_WRONLY | O_CREAT | O_TRUNC,
				STANDARD_FILE_PERMISSIONS);
		if (*output_fd < 0)
			return (ft_printf(STDERR_FILENO, "minishell: %s: %s\n",
					redirection->target, strerror(errno)), false);
	}
	else if (redirection->type == APPEND_OUT)
	{
		*output_fd = open(redirection->target, O_WRONLY | O_CREAT | O_APPEND,
				STANDARD_FILE_PERMISSIONS);
		if (*output_fd < 0)
			return (ft_printf(STDERR_FILENO, "minishell: %s: %s\n",
					redirection->target, strerror(errno)), false);
	}
	return (true);
}

static bool	ft_prepare_command_redirection(t_redirection *redirection,
		t_redirection *last_input, int *input_fd, int *output_fd)
{
	// TODO: issue with last_input == NULL ??
	if (!redirection || !input_fd || !output_fd)
		return (false);
	while (redirection)
	{
		if (redirection->type == HEREDOC || redirection->type == REDIRECT_IN)
		{
			if (!ft_prepare_command_inputs(redirection, last_input, input_fd))
				return (false);
		}
		else if (redirection->type == REDIRECT_OUT
			|| redirection->type == APPEND_OUT)
		{
			if (*output_fd != -1)
			{
				close(*output_fd);
				*output_fd = -1;
			}
			if (!ft_prepare_command_outputs(redirection, output_fd))
				return (false);
		}
		redirection = redirection->next;
	}
	return (true);
}

bool	ft_prepare_command_io(t_redirection *redirection)
{
	t_redirection	*last_input;
	int				input_fd;
	int				output_fd;

	if (!redirection)
		return (true);
	input_fd = -1;
	output_fd = -1;
	last_input = ft_get_last_input_redirection(redirection);
	// TODO: should we protect if last_input == NULL ??
	// if (!last_input)
	// {
	// 	// Only process output redirections
	// 	while (redirection)
	// 	{
	// 		if (redirection->type == REDIRECT_OUT
	// 			|| redirection->type == APPEND_OUT)
	// 		{
	// 			if (!ft_prepare_command_outputs(redirection, &output_fd))
	// 				return (false);
	// 		}
	// 		redirection = redirection->next;
	// 	}
	// }
	// else
	// {
		// if (!ft_prepare_command_redirection(redirection, last_input, &input_fd,
				// &output_fd))
			// return (false);
	// }
	if (!ft_prepare_command_redirection(redirection, last_input, &input_fd,
			&output_fd))
		return (false);
	// Apply input redirection
	if (input_fd != -1)
	{
		if (!ft_apply_dup2(input_fd, STDIN_FILENO))
		{
			if (output_fd != -1)
				close(output_fd);
			return (false);
		}
		close(input_fd);
	}
	// Apply output redirection
	if (output_fd != -1)
	{
		if (!ft_apply_dup2(output_fd, STDOUT_FILENO))
			return (false);
		close(output_fd);
	}
	return (true);
}
