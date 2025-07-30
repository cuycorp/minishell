/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wait_all_pids.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 16:47:40 by jgossard          #+#    #+#             */
/*   Updated: 2025/07/30 15:27:05 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_wait_all_pids(t_exec_context *context)
{
	int	i;
	int	status;

	if (!context)
		return (false);
	i = 0;
	// TODO: last_status lead to error message by initializing it to 0 (e.g `chmod 000 infile` -> `< infile` should return "bash: infile: Permission denied")
	// last_status = 0;
	while (i < context->pid_count)
	{
		if (waitpid(context->pids[i], &status, 0) != -1)
		{
			if (context->last_pid && context->pids[i] == context->last_pid)
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
		else
			perror("minishell: waitpid failed");
		i++;
	}
	return (true);
}
