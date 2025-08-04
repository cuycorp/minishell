/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wait_all_pids.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 16:47:40 by jgossard          #+#    #+#             */
/*   Updated: 2025/08/04 13:59:45 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_process_exit_status(t_exec_context *context, pid_t pid)
{
	int	status;

	if (!context)
		return ;
	if (waitpid(pid, &status, 0) == -1)
	{
		ft_printf(STDERR_FILENO, "minishell: waitpid failed : %s\n", strerror(errno));
		return ;
	}
	if (context->last_pid && pid == context->last_pid)
	{
		// TODO: add signal exit in the following if-statement
		if (WIFEXITED(status))
			context->last_exit_code = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			context->last_exit_code = 128 + WTERMSIG(status);
		else
			context->last_exit_code = EXIT_FAILURE;
	}
}

bool	ft_wait_all_pids(t_exec_context *context)
{
	int	i;

	if (!context)
		return (false);
	i = 0;
	// TODO: last_status lead to error message by initializing it to 0 (e.g `chmod 000 infile` -> `< infile` should return "bash: infile: Permission denied")
	// last_status = 0;
	while (i < context->pid_count)
	{
		if (context->pids[i] != -1)
			ft_process_exit_status(context, context->pids[i]);
		i++;
	}
	return (true);
}
