/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wait_all_pids.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 16:47:40 by jgossard          #+#    #+#             */
/*   Updated: 2025/07/11 20:18:55 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_wait_all_pids(t_shell *data, int *last_pid)
{
	int	i;
	int	status;
	int	last_status;

	if (!data || !data->pids || data->pid_count < 0)
		return (-EXIT_FAILURE);
	i = 0;
	// TODO: lead to error message by initializing it to 0 (e.g `chmod 000 infile` -> `< infile` should return "bash: infile: Permission denied")
	last_status = 0;
	while (i < data->pid_count)
	{
		if (waitpid(data->pids[i], &status, 0) == -1)
		{
			perror("minishell: waitpid failed");
			return (EXIT_FAILURE);
		}
		if (last_pid && data->pids[i] == *last_pid)
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
