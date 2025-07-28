/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 15:22:57 by jgossard          #+#    #+#             */
/*   Updated: 2025/07/28 20:40:23 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool ft_fill_heredoc(int write_fd, const char *delimiter)
{
	char *line;

	if (write_fd < 0 || !delimiter)
		return (false);
	while (true)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0 &&
			ft_strlen(line) == ft_strlen(delimiter))
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, write_fd);
		ft_putstr_fd("\n", write_fd);
		free(line);
	}
	return (true);
}

static void	ft_exec_heredoc_child(int *pipe_fd, const char *delimiter)
{
	if (!pipe_fd || !delimiter)
		exit(EXIT_FAILURE);
	close(pipe_fd[READ_END]);
	if (!ft_fill_heredoc(pipe_fd[WRITE_END], delimiter))
		return (exit(EXIT_FAILURE));
	close(pipe_fd[WRITE_END]);
	exit(EXIT_SUCCESS);
}

static int	ft_exec_heredoc_parent(int *pipe_fd, int pid)
{
	int		status;

	if (!pipe_fd || pid < 0)
		return (-1);
	close(pipe_fd[WRITE_END]);
	if (waitpid(pid, &status, 0) == -1)
	{
		ft_printf(STDERR_FILENO, "minishell: error with waitpid - %s\n", strerror(errno));
		close(pipe_fd[READ_END]);
		return (-1);
	}
	return (pipe_fd[READ_END]);
}

// TODO: parameter can be simplify since delimiter is already part of the redirection
int	ft_exec_heredoc(t_redirection *redirections, char *delimiter)
{
	pid_t	pid;
	int		pipe_fd[2];

	if (!redirections || !delimiter)
		return (-1);
	if (pipe(pipe_fd) == -1)
		return (perror("Pipe failed!"), -1);
	pid = fork();
	if (pid < 0)
	{
		close(pipe_fd[READ_END]);
		close(pipe_fd[WRITE_END]);
		return (perror("failed to fork"), -1);
	}
	if (pid == 0)
		ft_exec_heredoc_child(pipe_fd, delimiter);
	return (ft_exec_heredoc_parent(pipe_fd, pid));
}
