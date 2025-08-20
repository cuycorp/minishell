/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_redirections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 16:58:08 by jgossard          #+#    #+#             */
/*   Updated: 2025/08/20 15:42:34 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exec_redirections(t_redirection *redirection, t_shell *data)
{
	t_exec_context	*context;
	pid_t			pid;

	if (!redirection || !data || !data->context)
		return (EXIT_FAILURE);
	context = data->context;
	pid = fork();
	if (pid < 0)
		return (ft_error_failed_to_fork("ft_exec_redirections"), EXIT_FAILURE);
	if (pid == 0)
	{
		if (!ft_prepare_command_io(redirection, context))
			ft_exit_child(data, EXIT_FAILURE);
		ft_handle_dup2_and_close_fd(context->input_fd, STDIN_FILENO, data);
		ft_handle_dup2_and_close_fd(context->output_fd, STDOUT_FILENO, data);
		ft_exit_child(data, EXIT_SUCCESS);
	}
	if (waitpid(pid, &context->last_exit_code, 0) == -1)
		return (ft_error_failed_waitpid("ft_exec_redirections"), EXIT_FAILURE);
	return (context->last_exit_code);
}
