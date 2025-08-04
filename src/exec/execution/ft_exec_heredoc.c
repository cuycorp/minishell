/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 15:22:57 by jgossard          #+#    #+#             */
/*   Updated: 2025/07/30 17:13:56 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	ft_fill_heredoc(int write_fd, const char *delimiter)
{
	char	*line;

	if (write_fd < 0 || !delimiter)
		return (false);
	while (true)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0
			&& ft_strlen(line) == ft_strlen(delimiter))
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
	dprintf(STDERR_FILENO, "ft_exec_heredoc_child: in function\n");

	if (!ft_fill_heredoc(pipe_fd[WRITE_END], delimiter))
	{
		close(pipe_fd[WRITE_END]);
		exit(EXIT_FAILURE);
	}

	close(pipe_fd[WRITE_END]);
	dprintf(STDERR_FILENO, "ft_exec_heredoc_child: end of function\n");
	exit(EXIT_SUCCESS);
}

static int	ft_exec_heredoc_parent(int *pipe_fd, int pid, t_signal_child sig,
		t_exec_context *context)
{
	// int	status;
	if (!pipe_fd || pid < 0 || !context)
		return (-1);
	dprintf(STDERR_FILENO, "ft_exec_heredoc_parent: in function\n");

	close(pipe_fd[WRITE_END]);
	// TODO: to keep?
	// if (context->pid_count < context->command_count)
	// {
	// 	ft_printf(STDERR_FILENO, "will add pid into context->pids\n");
	// 	context->pids[context->pid_count] = pid;
	// 	// context->pid_count++;
	// 	context->last_pid = pid;
	// }
	if (ft_waitpid(pid, context) == false)
		return (-1);
	dprintf(STDERR_FILENO, "ft_exec_heredoc_parent: after waitpid\n");
	if (!ft_restore_signal_parent_n_exit_heredoc(&sig, context->last_exit_code,
			pipe_fd[READ_END], context))
		return (-1);
	dprintf(STDERR_FILENO, "ft_exec_heredoc_parent: after ft_restore_signal_parent_n_exit_heredoc\n");

	// context->pids[context->pid_count++] = -1;
	dprintf(STDERR_FILENO, "ft_exec_heredoc_parent: in function\n");
	ft_printf(STDERR_FILENO, "ft_exec_heredoc_parent: context->last_exit_code = %d\n", context->last_exit_code);
	return (pipe_fd[READ_END]);
}

int	ft_exec_heredoc(t_redirection *redirections, char *delimiter,
		t_exec_context *context)
{
	pid_t			pid;
	int				pipe_fd[2];
	t_signal_child	sig;

	if (!redirections || !delimiter)
		return (-1);
	if (pipe(pipe_fd) == -1)
		return (ft_printf(STDERR_FILENO, "minishell: error: failed to pipe - %s\n", strerror(errno)), -1);
	ft_set_signal_parent(&sig);
	pid = fork();
	if (pid < 0)
	{
			close(pipe_fd[READ_END]);
			close(pipe_fd[WRITE_END]);
			ft_printf(STDERR_FILENO, "minishell: error: failed to fork - %s\n",
				strerror(errno));
			return (-1);
	}
	if (pid == 0)
	{
			ft_set_signal_child(false);
			ft_exec_heredoc_child(pipe_fd, delimiter);
	}
	return (ft_exec_heredoc_parent(pipe_fd, pid, sig, context));
}
