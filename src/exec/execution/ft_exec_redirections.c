/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_redirections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 16:58:08 by jgossard          #+#    #+#             */
/*   Updated: 2025/07/30 17:12:46 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exec_redirections(t_redirection *redirection, t_exec_context *context)
{
	pid_t	pid;

	if (!redirection || !context)
		return (EXIT_FAILURE);
	pid = fork();
	if (pid < 0)
	{
		ft_printf(STDERR_FILENO, "minishell: error : failed to fork - %s\n",
			strerror(errno));
		return (EXIT_FAILURE);
	}
	if (pid == 0)
	{
		if (!ft_prepare_command_io(redirection, context))
			exit(EXIT_FAILURE);
		exit(EXIT_SUCCESS);
	}
	if (context->pid_count < context->command_count)
	{
		context->pids[context->pid_count++] = pid;
		context->last_pid = pid;
	}
	return (context->last_exit_code);
}
