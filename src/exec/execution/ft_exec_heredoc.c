/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 15:22:57 by jgossard          #+#    #+#             */
/*   Updated: 2025/08/04 15:00:22 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	ft_fill_heredoc(int write_fd, const char *delimiter)
{
	char	*line;
	size_t	delimiter_len;

	if (write_fd < 0 || !delimiter)
		return (false);
	delimiter_len = ft_strlen(delimiter);
	while (true)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strncmp(line, delimiter, delimiter_len) == 0
			&& ft_strlen(line) == delimiter_len)
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

static void	ft_exec_heredoc_child(int *pipe_fd, const char *delimiter,
		t_shell *data)
{
	if (!delimiter || !data)
	{
		ft_close_fds(pipe_fd);
		ft_exit_child(data, EXIT_FAILURE);
	}
	if (!pipe_fd)
		ft_exit_child(data, EXIT_FAILURE);
	ft_set_signal_child(true);
	close(pipe_fd[READ_END]);
	if (!ft_fill_heredoc(pipe_fd[WRITE_END], delimiter))
	{
		close(pipe_fd[WRITE_END]);
		ft_exit_child(data, EXIT_FAILURE);
	}
	close(pipe_fd[WRITE_END]);
	ft_exit_child(data, EXIT_SUCCESS);
}

static int	ft_exec_heredoc_parent(int *pipe_fd, int pid, t_signal_child sig,
		t_shell *data)
{

	if (!pipe_fd || !data || !data->context)
		return (-1);
	if (pid < 0)
	{
		ft_close_fds(pipe_fd);
		return (-1);
	}
	close(pipe_fd[WRITE_END]);
	if (waitpid(pid, &data->context->last_exit_code, 0) == -1)
	{
		ft_printf(STDERR_FILENO, "minishell: error: error with waitpid - %s\n",
			strerror(errno));
		close(pipe_fd[READ_END]);
		return (-1);
	}
	if (!ft_restore_signal_parent_heredoc(&sig, data, pipe_fd[READ_END]))
		return (-1);
	ft_mark_pids_reaped(data->context);
	return (pipe_fd[READ_END]);
}

int	ft_exec_heredoc(t_redirection *redirections, char *delimiter, t_shell *data)
{
	pid_t			pid;
	int				pipe_fd[2];
	t_signal_child	sig;

	if (!redirections || !delimiter || !data)
		return (-1);
	if (pipe(pipe_fd) == -1)
	{
		ft_printf(STDERR_FILENO, "minishell: heredoc: failed to pipe - %s\n",
			strerror(errno));
		return (-1);
	}
	ft_set_signal_parent(&sig);
	pid = fork();
	if (pid < 0)
	{
		ft_close_fds(pipe_fd);
		ft_printf(STDERR_FILENO, "minishell: heredoc: failed to fork - %s\n",
			strerror(errno));
		return (-1);
	}
	if (pid == 0)
		ft_exec_heredoc_child(pipe_fd, delimiter, data);
	return (ft_exec_heredoc_parent(pipe_fd, pid, sig, data));
}
