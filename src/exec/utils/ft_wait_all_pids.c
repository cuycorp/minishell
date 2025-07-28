/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wait_all_pids.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 16:47:40 by jgossard          #+#    #+#             */
/*   Updated: 2025/07/28 20:40:51 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_wait_all_pids(t_shell *data, t_exec_context *context)
{
	int	i;
	int	status;
	int	last_status;

	if (!data || !context)
		return (EXIT_FAILURE);
	i = 0;
	// TODO: lead to error message by initializing it to 0 (e.g `chmod 000 infile` -> `< infile` should return "bash: infile: Permission denied")
	last_status = 0;
	while (i < context->pid_count)
	{
		if (waitpid(context->pids[i], &status, 0) == -1)
		{
			perror("minishell: waitpid failed");
			return (EXIT_FAILURE);
		}
		if (context->last_pid && context->pids[i] == context->last_pid)
		{
			// TODO: add signal exit in the following if-statement
			if (WIFEXITED(status))
				last_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				last_status = 128 + WTERMSIG(status);
		}
		i++;
	}
	return (last_status);
}
