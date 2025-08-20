/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 15:22:57 by jgossard          #+#    #+#             */
/*   Updated: 2025/08/20 16:22:45 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_handle_empty_line_exit_code(void)
{
	if (g_exit_code == 130)
		return (130);
	return (0);
}

static int	ft_fill_heredoc(int write_fd, const char *delimiter)
{
	char	*line;
	size_t	delimiter_len;

	if (write_fd < 0 || !delimiter)
		return (EXIT_FAILURE);
	delimiter_len = ft_strlen(delimiter);
	while (true)
	{
		line = readline("> ");
		if (!line)
			return (ft_handle_empty_line_exit_code());
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
	return (EXIT_SUCCESS);
}

static void	ft_exec_heredoc_child(int *pipe_fd, const char *delimiter,
		t_shell *data)
{
	int	result;

	if (!delimiter || !data)
	{
		ft_close_pipe_fds(pipe_fd);
		ft_exit_child(data, EXIT_FAILURE);
	}
	if (!pipe_fd)
		ft_exit_child(data, EXIT_FAILURE);
	ft_set_signal_child_heredoc();
	close(pipe_fd[READ_END]);
	result = ft_fill_heredoc(pipe_fd[WRITE_END], delimiter);
	close(pipe_fd[WRITE_END]);
	ft_exit_child(data, result);
}

static int	ft_exec_heredoc_parent(int *pipe_fd, int pid, t_signal_child sig,
		t_shell *data)
{
	if (!pipe_fd || !data || !data->context)
		return (-1);
	if (pid < 0)
	{
		ft_close_pipe_fds(pipe_fd);
		return (-1);
	}
	close(pipe_fd[WRITE_END]);
	if (waitpid(pid, &data->context->last_exit_code, 0) == -1)
	{
		ft_error_failed_waitpid("ft_exec_heredoc_parent");
		close(pipe_fd[READ_END]);
		return (-1);
	}
	if (!ft_restore_signal_parent_heredoc(&sig, data, pipe_fd[READ_END]))
		return (-1);
	return (pipe_fd[READ_END]);
}

int	ft_exec_heredoc(t_redirection *redirection, char *delimiter, t_shell *data)
{
	pid_t			pid;
	int				pipe_fd[2];
	t_signal_child	sig;

	if (!redirection || !delimiter || !data)
		return (-1);
	if (pipe(pipe_fd) == -1)
	{
		ft_error_failed_to_pipe("ft_exec_heredoc");
		return (-1);
	}
	ft_set_signal_parent(&sig);
	pid = fork();
	if (pid < 0)
	{
		ft_close_pipe_fds(pipe_fd);
		ft_error_failed_to_fork("ft_exec_heredoc");
		return (-1);
	}
	if (pid == 0)
		ft_exec_heredoc_child(pipe_fd, delimiter, data);
	return (ft_exec_heredoc_parent(pipe_fd, pid, sig, data));
}
