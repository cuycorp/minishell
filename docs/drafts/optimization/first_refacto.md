I have done a first step of refactoring, here is my code:
void	ft_handle_shell(t_shell *data)
{
	...
	while (1)
	{
		if (data->ast_root)
		{
			exit_code = ft_executor(data->ast_root, data);
			ft_printf(STDOUT_FILENO, "exit code = %d\n", exit_code);
		}
		ft_reset_shell(data);
	}
	...
}

int	ft_execute_ast_tree(t_ast_node *node, t_shell *data,
		int input_fd, int *last_pid)
{
	if (!node || !data || !last_pid || input_fd < 0) // TODO: check on current_infile_fd correct?
		return (EXIT_FAILURE);
	if (node->type == AST_PIPE)
		return (ft_exec_pipe_node(node, data, input_fd, last_pid));
	else if (node->type == AST_SIMPLE_COMMAND)
		return (ft_exec_simple_command(node->command_data, data, input_fd, last_pid));
	else if (node->type == AST_LOGICAL_AND)
		return (ft_exec_logical_and(node, data, input_fd, last_pid));
	else if (node->type == AST_LOGICAL_OR)
		return (ft_exec_logical_or(node, data, input_fd, last_pid));
	else if (node->type == AST_REDIRECTION)
	{
		if (!ft_prepare_command_io(node->redirection_data))
			return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

int	ft_executor(t_ast_node *root, t_shell *data)
{
	int	last_pid;
	int	result;

	if (!root || !data) // TODO: add last_pid
		return (EXIT_FAILURE);
	last_pid = -1;
	data->pid_count = 0;
	data->pids = malloc(sizeof(pid_t) * ft_count_cmd_nodes(data->ast_root));
	if (!data->pids)
		return (perror("Error: malloc failed"), EXIT_FAILURE);
	// Process Heredocs
	if (!ft_process_heredocs(root))
		return (EXIT_FAILURE);
	result = ft_execute_ast_tree(root, data, STDIN_FILENO, &last_pid);
	return (ft_wait_all_pids(data, &last_pid));
}

static bool	ft_handle_heredoc(t_redirection *redirection)
{
	int	fd;

	while (redirection)
	{
		if (redirection->type == HEREDOC && redirection->heredoc_fd == -1)
		{
			fd = ft_exec_heredoc(redirection, redirection->target);
			if (fd == -1)
				return (false);
			redirection->heredoc_fd = fd;
		}
		redirection = redirection->next;
	}
	return (true);
}

bool	ft_process_heredocs(t_ast_node *root) // TODO: renamed it to something like ft_prepare_all_heredocs
{
	if (!root)
		return (true);
	if (root->type == AST_REDIRECTION && root->redirection_data)
	{
		if (!ft_handle_heredoc(root->redirection_data))
			return (false);
	}
	if (root->type == AST_SIMPLE_COMMAND && root->command_data)
	{
		if (!ft_handle_heredoc(root->command_data->redirection))
			return (false);
	}
	return (
		ft_process_heredocs(root->left) && ft_process_heredocs(root->right));
}

int	ft_exec_heredoc(t_redirection *redirections, char *delimiter)
{
	pid_t	pid;
	int		pipe_fd[2];
	int		status;
	char	*line;

	if (!redirections || !delimiter)
		return (-1);
	dprintf(g_log,"ft_exec_heredoc : enter function\n");

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
	{
		dprintf(g_log,"ft_exec_heredoc : enter child process\n");

		close(pipe_fd[READ_END]);
		while (1)
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
			ft_putstr_fd(line, pipe_fd[WRITE_END]);
			ft_putstr_fd("\n", pipe_fd[WRITE_END]);
			free(line);
		}
		close(pipe_fd[WRITE_END]);
		dprintf(g_log,"ft_exec_heredoc : exit child process with exit code = %d\n", EXIT_SUCCESS);
		exit(EXIT_SUCCESS);
	}
	close(pipe_fd[WRITE_END]);
	if (waitpid(pid, &status, 0) == -1)
	{
		perror("minishell: waitpid failed");
		ft_putstr_fd("error in waitpid of exec_heredoc\n", STDERR_FILENO);
		close(pipe_fd[READ_END]);
		return (-1);
	}
	// return (true);
	dprintf(g_log,"ft_exec_heredoc : exit function with pipe_fd[%d] = %d\n", READ_END, pipe_fd[READ_END]);
	return (pipe_fd[READ_END]);
}

static t_redirection	*ft_get_last_input_redirection(t_redirection *redirection)
{
	t_redirection	*last_input;

	if (!redirection)
		return (NULL);
	last_input = NULL;
	while (redirection)
	{
		if (redirection->type == HEREDOC || redirection->type == REDIRECT_IN)
			last_input = redirection;
		redirection = redirection->next;
	}
	return (last_input);
}

static bool	ft_prepare_command_inputs(t_redirection *redirection,
		t_redirection *last_input, int *input_fd)
{
	int	fd;

	if (!redirection || !last_input || !input_fd)
		return (false);
	if (redirection->type == HEREDOC)
	{
		if (redirection->heredoc_fd == -1)
			return (false);
		if (redirection == last_input)
			*input_fd = redirection->heredoc_fd;
		else
			close(redirection->heredoc_fd);
	}
	else if (redirection->type == REDIRECT_IN)
	{
		fd = open(redirection->target, O_RDONLY);
		if (fd < 0)
			return (ft_printf(STDERR_FILENO, "minishell: %s: %s\n",
					redirection->target, strerror(errno)), false);
		if (redirection == last_input)
			*input_fd = fd;
		else
			close(fd);
	}
	return (true);
}

static bool	ft_prepare_command_outputs(t_redirection *redirection,
		int *output_fd)
{
	if (!redirection || !output_fd)
		return (false);
	if (redirection->type == REDIRECT_OUT)
	{
		*output_fd = open(redirection->target, O_WRONLY | O_CREAT | O_TRUNC,
				STANDARD_FILE_PERMISSIONS);
		if (*output_fd < 0)
			return (ft_printf(STDERR_FILENO, "minishell: %s: %s\n",
					redirection->target, strerror(errno)), false);
	}
	else if (redirection->type == APPEND_OUT)
	{
		*output_fd = open(redirection->target, O_WRONLY | O_CREAT | O_APPEND,
				STANDARD_FILE_PERMISSIONS);
		if (*output_fd < 0)
			return (ft_printf(STDERR_FILENO, "minishell: %s: %s\n",
					redirection->target, strerror(errno)), false);
	}
	return (true);
}

static bool	ft_prepare_command_redirection(t_redirection *redirection,
		t_redirection *last_input, int *input_fd, int *output_fd)
{
	// TODO: issue with last_input == NULL ??
	if (!redirection || !last_input || !input_fd || !output_fd)
		return (false);
	while (redirection)
	{
		if (redirection->type == HEREDOC || redirection->type == REDIRECT_IN)
		{
			if (!ft_prepare_command_inputs(redirection, last_input, input_fd))
				return (false);
		}
		else if (redirection->type == REDIRECT_OUT
			|| redirection->type == APPEND_OUT)
		{
			if (!ft_prepare_command_outputs(redirection, output_fd))
				return (false);
		}
		redirection = redirection->next;
	}
	return (true);
}

bool	ft_prepare_command_io(t_redirection *redirection)
{
	t_redirection	*last_input;
	int				input_fd;
	int				output_fd;

	if (!redirection)
		return (true);
	input_fd = -1;
	output_fd = -1;
	last_input = ft_get_last_input_redirection(redirection);
	// TODO: should we protect if last_input == NULL ??
	if (!ft_prepare_command_redirection(redirection, last_input, &input_fd,
			&output_fd))
		return (false);
	if (input_fd != -1 && !ft_apply_dup2(input_fd, STDIN_FILENO))
		return (false);
	if (output_fd != -1 && !ft_apply_dup2(output_fd, STDOUT_FILENO))
		return (false);
	// if (input_fd != -1)
	// 	close(input_fd);
	// if (output_fd != 1)
	// 	close(output_fd);
	return (true);
}

bool	ft_apply_dup2(int oldfd, int newfd)
{
	if (oldfd < 0 || newfd < 0)
		return (false);
	if (dup2(oldfd, newfd) == -1)
	{
		ft_putstr_fd("Error: dup2\n",STDERR_FILENO);
		close(oldfd);
		return (false);
	}
	close(oldfd);
	return (true);
}

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
		return (perror("failed to fork"), EXIT_FAILURE);
	}
	if (pid == 0)
	{
		close(pipe_fd[READ_END]);
		if (!ft_apply_dup2(pipe_fd[WRITE_END], STDOUT_FILENO))
			exit(EXIT_FAILURE);
		if (input_fd != STDIN_FILENO)
		{
			if (!ft_apply_dup2(input_fd, STDIN_FILENO))
				exit(EXIT_FAILURE);
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

int	ft_exec_simple_command(t_command *command, t_shell *data, int input_fd, int *last_pid)
{
	pid_t	pid;
	// int		exit_code;
	// bool	has_input_redirection;
	bool	is_parent_builtin;

	if (!command || !data || !last_pid || input_fd < 0) // TODO: add check on input_fd
		return (EXIT_FAILURE);
	is_parent_builtin = ft_is_parent_builtins(command->name);
	if (is_parent_builtin && input_fd == STDIN_FILENO)
	{
		if (!ft_prepare_command_io(command->redirection))
			return (EXIT_FAILURE);
		return (ft_exec_parent_builtin(command, data));
	}
	// FORK
	pid = fork();
	if (pid < 0)
	{
		// if (input_fd != STDIN_FILENO)
		// 	close(input_fd);
		return (perror("failed to fork"), EXIT_FAILURE);
	}
	if (pid == 0)
	{
		// has_input_redirection = ft_has_input_redirection(command->redirection);
		// if (!has_input_redirection && input_fd != STDIN_FILENO)
		// {
		// 	// Todo: add check on dup2 if == -1
		// 	if (!ft_apply_dup2(input_fd, STDIN_FILENO))
		// 		exit(EXIT_FAILURE);
		// 	close(input_fd); // TODO: to keep?
		// }
		if (input_fd != STDIN_FILENO)
		{
			if (!ft_apply_dup2(input_fd, STDIN_FILENO))
				exit(EXIT_FAILURE);
			// close(input_fd);
		}
		if (!ft_prepare_command_io(command->redirection))
			exit(EXIT_FAILURE);
		if (ft_is_builtin_function(command->name))
			exit(ft_exec_builtin(command, data));
		exit(ft_exec_command(command, data));
	}
	if (input_fd != STDIN_FILENO)
		close(input_fd);
	if (data->pid_count < data->command_count)
	{
		data->pids[data->pid_count] = pid;
		data->pid_count++;
		*last_pid = pid;
	}
	return (EXIT_SUCCESS);
}

Questions:
1. with this new code, i have some issue:

- with only redirection: i have been able to close the heredoc but i think i have an issue with the redirection since the exit value is used by as a new prompt instead of closing the current line
Oh-My-Shell > << eof
Token[0] : value = <<, value length = 2, token type = TOKEN_HEREDOC
Token[1] : value = eof, value length = 3, token type = TOKEN_WORD
> hello from heredoc
> eof
exit code = 0
Oh-My-Shell > hello from heredoc
Token[0] : value = hello, value length = 5, token type = TOKEN_WORD
Token[1] : value = from, value length = 4, token type = TOKEN_WORD
Token[2] : value = heredoc, value length = 7, token type = TOKEN_WORD
exit code = 0
Oh-My-Shell > Minishell: hello : command not found

- when i used a simple command like `ls`, i have well the result but the prompt does not closed
- same issue with command like `cat < readme.md`, i have the result but the result is used as a new prompt and then the prompt does not closed

Oh-My-Shell >cat < readme.md
Token[0] : value = cat, value length = 3, token type = TOKEN_WORD
Token[1] : value = <, value length = 1, token type = TOKEN_REDIRECT_IN
Token[2] : value = readme.md, value length = 9, token type = TOKEN_WORD
Token[3] : value = , value length = 0, token type = TOKEN_END_OF_LINE
exit code = 0
Oh-My-Shell > # Minishell


## excel
text from my makefile

can you help me fix it?
