/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_pipe_node.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 15:07:24 by jgossard          #+#    #+#             */
/*   Updated: 2025/07/25 19:00:49 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exec_pipe_node(t_ast_node *root, t_shell *data, int input_fd,
		int *last_pid)
{
	pid_t	pid;
	int		pipe_fd[2];
	int		result;

	if (!root || !data) // TODO: update check on parameter
		return (EXIT_FAILURE);
	if (pipe(pipe_fd) == -1)
		return (perror("Pipe failed!"), EXIT_FAILURE);
	pid = fork();
	if (pid < 0)
	{
		close(pipe_fd[READ_END]);
		close(pipe_fd[WRITE_END]);
		if (input_fd != STDIN_FILENO)
			close(input_fd);
		return (perror("failed to fork"), EXIT_FAILURE);
	}
	if (pid == 0)
	{
		close(pipe_fd[READ_END]);
		// Redirect stdout to pipe
		if (!ft_apply_dup2(pipe_fd[WRITE_END], STDOUT_FILENO))
			exit(EXIT_FAILURE);
		close(pipe_fd[WRITE_END]);
		// Handle input from previous pipe
		if (input_fd != STDIN_FILENO)
		{
			if (!ft_apply_dup2(input_fd, STDIN_FILENO))
				exit(EXIT_FAILURE);
			close(input_fd);
		}
		exit(ft_execute_ast_tree(root->left, data, input_fd, last_pid));
	}
	close(pipe_fd[WRITE_END]);
	if (input_fd != STDIN_FILENO)
		close(input_fd);
	if (data->pid_count < data->command_count)
	{
		data->pids[data->pid_count] = pid;
		data->pid_count++;
	}
	result = ft_execute_ast_tree(root->right, data, pipe_fd[READ_END], last_pid);
	close(pipe_fd[READ_END]);
	return (result);
}
/*
//       PIPE
//      /    \
//    PIPE   cmd1
//   /    \
// cmd2   cmd3
*/

/*
//       Simple_Command
//      /    \
//    PIPE   cmd1
//   /    \
// cmd2   cmd3
*/
