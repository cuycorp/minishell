/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_redirections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 16:58:08 by jgossard          #+#    #+#             */
/*   Updated: 2025/07/28 20:36:54 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO:keep the code above?
static void ft_wait_and_set_exit_code(int *exit_code)
{
	int	status;

	// TODO: add check on parameter
	status = 0;
	if (WIFEXITED(status))
		*exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		*exit_code = 128 + WTERMSIG(status);
	else
		*exit_code = EXIT_FAILURE;
}
// TODO: to delete and keep the code above?
int	ft_exec_redirections(t_redirection *redirection, t_exec_context *context)
{
	pid_t	pid;
	int exit_code;
	int status;

	if (!redirection || !context)
		return (EXIT_FAILURE);
	pid = fork();
	if (pid < 0)
		return (perror("failed to fork"), EXIT_FAILURE);
	if (pid == 0)
	{
		if (!ft_prepare_command_io(redirection, context))
			exit(EXIT_FAILURE);
		exit(EXIT_SUCCESS);
	}
	if (waitpid(pid, &status, 0) == -1)
	{
		perror("minishell: waitpid failed");
		return (EXIT_FAILURE);
	}
	ft_wait_and_set_exit_code(&exit_code);
	return (exit_code);
}
