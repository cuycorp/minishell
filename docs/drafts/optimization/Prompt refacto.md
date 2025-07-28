I am working on minishell execution part. For the parsing part, i did a recursive descent parsing to be able to build an ast tree with a left-associativity

here is my code:

static void	ft_close_heredocs_fd(t_ast_node *node)
{
	t_redirection	*redirection;

	if (!node)
		return ;
	if (node->type == AST_SIMPLE_COMMAND && node->command_data)
	{
		redirection = node->command_data->redirection;
		while (redirection)
		{
			if (redirection->type == HEREDOC && redirection->heredoc_fd != -1)
			{
				close(redirection->heredoc_fd);
				redirection->heredoc_fd = -1;
			}
			redirection = redirection->next;
		}
	}
	ft_close_heredocs_fd(node->left);
	ft_close_heredocs_fd(node->right);
}

static void	ft_reset_shell(t_shell *data)
{
	if (!data)
		return ;
	if (data->input)
	{
		free(data->input);
		data->input = NULL;
	}
	if (data->tokens_list)
		ft_free_tokens_list(&data->tokens_list);
	if (data->ast_root)
		ft_free_ast_tree(&data->ast_root);
	if (data->pids)
	{
		free(data->pids);
		data->pids = NULL;
	}
	if (data->ast_root)
		ft_close_heredocs_fd(data->ast_root);
	data->pid_count = 0;
}

void	ft_handle_shell(t_shell *data)
{
	...
	while (1)
	{
		if (data->ast_root)
		{
			ft_print_ast_node(data->ast_root);
			if (!ft_process_heredocs(data->ast_root))
			{
				ft_printf(STDERR_FILENO, "heredoc processing failed\n");
				ft_reset_shell(data);
				continue;
			}
			data->command_count = ft_count_cmd_nodes(data->ast_root);
			if (data->command_count == 0)
			{
				if (data->ast_root->type == AST_REDIRECTION)
				{
					exit_code = ft_exec_redirections(data->ast_root->redirection_data);
					ft_printf(STDOUT_FILENO, "exit code = %d\n", exit_code);
				}
				else
				{
					ft_printf(STDERR_FILENO, "Execution failed\n");
				}
			}
			else
			{
				data->pids = malloc(sizeof(pid_t) * data->command_count);
				if (!data->pids)
				{
					(perror("Error: malloc failed"));
					ft_reset_shell(data);
					continue ;
				}
				last_pid = -1;
				data->pid_count = 0;
				if (ft_executor(data->ast_root, data, STDIN_FILENO, &last_pid) == EXIT_SUCCESS)
				{
					exit_code = ft_wait_all_pids(data, &last_pid);
					ft_printf(STDOUT_FILENO, "exit code = %d\n", exit_code);
				}
				else
					ft_printf(STDERR_FILENO, "Execution failed\n");
			}
		}

		ft_reset_shell(data);
	}
	// TODO: add clear_history in ft_reset_shell????
	free(prompt);
}

my ast_tree looks the following:

{
	root:{
		type: AST_PIPE,
		left: {
			type: AST_SIMPLE_COMMAND,
			left: NULL,
			right: NULL,
			value: NULL,
			redirection_data: NULL,
			command_data: {
				args: ["cat", NULL],
				name: "/bin/cat",
				redirection: NULL;
			}
		},
		right: {
			type: AST_SIMPLE_COMMAND,
			left: NULL,
			right: NULL,
			value: NULL,
			redirection_data: NULL,
			command_data: {
				args: ["ls", NULL],
				name: "/bin/ls",
				redirection: NULL;
			}
		},
		value: NULL,
		redirection_data: NULL,
		command_data: NULL
	}
}

here the code for the execution part and redirections:

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

bool	ft_process_heredocs(t_ast_node *root)
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
	if (!ft_process_heredocs(root->left))
		return (false);
	if (!ft_process_heredocs(root->right))
		return (false);
	return (true);
}

int	ft_execute_ast_tree(t_ast_node *node, t_shell *data,
		int current_infile_fd, int *last_pid)
{
	int	result;

	if (!node || !data)
		return (EXIT_FAILURE);
	if (node->type == AST_PIPE)
		return (ft_exec_pipe_node(node, data, current_infile_fd, last_pid));
	else if (node->type == AST_SIMPLE_COMMAND)
		return (ft_exec_simple_command(node->command_data, data, current_infile_fd, last_pid));
	else if (node->type == AST_LOGICAL_AND)
	{
		result = ft_execute_ast_tree(node->left, data, current_infile_fd, last_pid);
		if (result == EXIT_SUCCESS)
			return (ft_execute_ast_tree(node->right, data, current_infile_fd, last_pid));
		return (result); // Todo: to keep?
	}
	else if (node->type == AST_LOGICAL_OR)
	{
		result = ft_execute_ast_tree(node->left, data, current_infile_fd, last_pid);
		if (result == EXIT_FAILURE)
			return (ft_execute_ast_tree(node->right, data, current_infile_fd, last_pid));
		return (result); // Todo: to keep?
	}
	return (EXIT_FAILURE);
}

int	ft_exec_heredoc(t_redirection *redirections, char *delimiter)
{
	pid_t	pid;
	int		pipe_fd[2];
	int		status;
	char	*line;

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
	{
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
	return (pipe_fd[READ_END]);
}
static void ft_wait_and_set_exit_code(int *exit_code)
{
	int	status;

	status = 0;
	if (WIFEXITED(status))
		*exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		*exit_code = 128 + WTERMSIG(status);
	else
		*exit_code = EXIT_FAILURE;
}

int	ft_exec_redirections(t_redirection *redirection)
{
	pid_t	pid;
	int exit_code;
	int status;

	if (!redirection)
		return (EXIT_FAILURE);
	pid = fork();
	if (pid < 0)
		return (perror("failed to fork"), EXIT_FAILURE);
	if (pid == 0)
	{
		if (!ft_setup_redirection(redirection))
			return (exit(EXIT_FAILURE), EXIT_FAILURE); // TODO: simplify this line
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

int	ft_executor(t_ast_node *root, t_shell *data, int current_infile_fd,
		int *last_pid)
{
	// data->pid_count = 0;
	if (!root || !data)
		return (EXIT_FAILURE);
	if (ft_execute_ast_tree(root, data, current_infile_fd, last_pid) != 0)
		return (EXIT_FAILURE);
	// close(current_infile_fd);
	return (EXIT_SUCCESS);
}

int	ft_exec_pipe_node(t_ast_node *root, t_shell *data, int current_infile_fd,
		int *last_pid)
{
	pid_t	pid;
	int		pipe_fd[2];
	int		result;
	int		exit_code;

	if (!root || !data)
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
		// Todo: add check on dup2 if == -1
		if (!ft_apply_dup2(pipe_fd[WRITE_END], STDOUT_FILENO))
			exit(EXIT_FAILURE);
		close(pipe_fd[WRITE_END]);
		if (current_infile_fd != STDIN_FILENO)
		{
			if (dup2(current_infile_fd, STDIN_FILENO) == -1)
				exit(EXIT_FAILURE);
			close(current_infile_fd);
		}
		exit_code = ft_execute_ast_tree(root->left, data, current_infile_fd, last_pid);
		exit(exit_code);
	}
	close(pipe_fd[WRITE_END]);
	if (current_infile_fd != STDIN_FILENO)
		close(current_infile_fd);
	if (data->pid_count < data->command_count)
	{
		data->pids[data->pid_count] = pid;
		data->pid_count++;
	}
	result = ft_execute_ast_tree(root->right, data, pipe_fd[READ_END], last_pid);
	close(pipe_fd[READ_END]);
	return (result);
}

static bool	ft_has_input_redirection(t_redirection *redirection)
{
	if (!redirection)
		return (false);
	while (redirection)
	{
		if (redirection->type == HEREDOC || redirection->type == REDIRECT_IN)
			return (true);
		redirection = redirection->next;
	}
	return (false);
}

bool	ft_is_parent_builtins(char *command_name)
{
	if (!command_name)
		return (false);
	return (ft_strncmp(command_name, CD, ft_strlen(CD)) == 0
		|| ft_strncmp(command_name, EXPORT, ft_strlen(EXPORT)) == 0
		|| ft_strncmp(command_name, UNSET, ft_strlen(UNSET)) == 0
		|| ft_strncmp(command_name, EXIT, ft_strlen(EXIT)) == 0);
}

int	ft_exec_simple_command(t_command *command, t_shell *data, int input_fd, int *last_pid)
{
	pid_t	pid;
	int		exit_code;
	bool	has_input_redirection;
	bool	is_parent_builtin;

	if (!command || !data || !last_pid || input_fd < 0) // TODO: add check on input_fd
		return (EXIT_FAILURE);
	is_parent_builtin = ft_is_parent_builtins(command->name);
	if (is_parent_builtin && input_fd == STDIN_FILENO)
	{
		if (!ft_setup_redirection(command->redirection))
			return (EXIT_FAILURE);
		exit_code = ft_exec_parent_builtin(command, data);
		*last_pid = -1;
		return (exit_code);
	}
	// FORK
	pid = fork();
	if (pid < 0)
	{
		if (input_fd != STDIN_FILENO)
			close(input_fd);
		return (perror("failed to fork"), EXIT_FAILURE);
	}
	if (pid == 0)
	{
		has_input_redirection = ft_has_input_redirection(command->redirection);
		if (!has_input_redirection && input_fd != STDIN_FILENO)
		{
			// Todo: add check on dup2 if == -1
			if (!ft_apply_dup2(input_fd, STDIN_FILENO))
				exit(EXIT_FAILURE);
			close(input_fd); // TODO: to keep?
		}
		if (input_fd != STDIN_FILENO)
			close(input_fd);
		if (!ft_setup_redirection(command->redirection))
			exit(EXIT_FAILURE); // TODO: simplify this line by simply calling exit(EXIT_FAILURE) but not sure
		if (ft_is_builtin_function(command->name))
			exit_code = ft_exec_builtin(command, data);
		else
			exit_code = ft_exec_command(command, data);
		exit(exit_code);
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

static t_redirection	*ft_get_last_input_redirection(t_redirection *redirection)
{
	t_redirection	*last_input;
	t_redirection	*current;

	if (!redirection)
		return (NULL);
	current = redirection;
	last_input = NULL;
	while (current)
	{
		if (current->type == HEREDOC || current->type == REDIRECT_IN)
			last_input = current;
		current = current->next;
	}
	return (last_input);
}

static int	ft_exec_redirect_in(t_redirection *redirections)
{
	int	fd;

	if (!redirections)
		return (-1);
	fd = -1;
	if (redirections->type == REDIRECT_IN)
	{
		fd = open(redirections->target, O_RDONLY);
		if (fd < 0)
		{
			ft_printf(STDERR_FILENO, "minishell:  %s: %s\n", redirections->target, strerror(errno));
			return (-1);
		}
	}
	return (fd);
}

static bool	ft_handle_inputs(t_redirection *redirection, t_redirection *last_input, int *input_fd)
{
	int	fd;

	if (!redirection || !last_input || !input_fd)
		return (false);
	if (redirection->type == HEREDOC)
	{
		// fd = ft_exec_heredoc(redirection, redirection->target);
		fd = redirection->heredoc_fd;
		if (fd == -1)
			return (false);
		if (redirection == last_input)
			*input_fd = fd;
		else
			close(fd);
	}
	else if (redirection->type == REDIRECT_IN)
	{
		int fd = ft_exec_redirect_in(redirection);
		if (fd == -1)
			return (false);
		if (redirection == last_input)
			*input_fd = fd;
		else
			close(fd);
	}
	return (true);
}

bool	ft_setup_redirection(t_redirection *redirection)
{
	t_redirection	*last_input;
	int				input_fd;
	// int				output_fd;

	if (!redirection)
		return (true);
	dprintf(g_log,"ft_setup_redirection : enter function\n");
	last_input = ft_get_last_input_redirection(redirection);
	input_fd = -1;
	// output_fd = -1;
	while (redirection)
	{
		if (redirection->type == HEREDOC || redirection->type == REDIRECT_IN)
		{
			if (!ft_handle_inputs(redirection, last_input, &input_fd))
				return (false);
		}
		else if (redirection->type == REDIRECT_OUT || redirection->type == APPEND_OUT)
		{
			if (!ft_apply_redirection(redirection))
				return (false);
		}
		redirection = redirection->next;
	}
	if (input_fd != -1)
	{
		if (dup2(input_fd, STDIN_FILENO) == -1)
		{
			close(input_fd);
			ft_putstr_fd("minishell: error on dup2 for heredoc\n", STDERR_FILENO);
			return (false);
		}
		close(input_fd);
	}
	dprintf(g_log,"ft_setup_redirection : exit function\n");
	return (true);
}

int	ft_exec_builtin(t_command *command, t_shell *data)
{
	if (!command || !data)
		return (EXIT_FAILURE);
	if (ft_strncmp(command->name, ECHO_BUILTIN, ft_strlen(ECHO_BUILTIN)) == 0)
		return (function_echo(command));
	else if (ft_strncmp(command->name, CD, ft_strlen(CD)) == 0)
		return (function_cd(&data, command));
	else if (ft_strncmp(command->name, PWD, ft_strlen(PWD)) == 0)
		return (function_pwd(data, command));
	else if (ft_strncmp(command->name, EXPORT, ft_strlen(EXPORT)) == 0)
		return (function_export(command, data));
	else if (ft_strncmp(command->name, UNSET, ft_strlen(UNSET)) == 0)
		return (function_unset(command, data));
	else if (ft_strncmp(command->name, ENV, ft_strlen(ENV)) == 0)
		return (function_env(command, data));
	// else if (ft_strncmp(command->name, EXIT, ft_strlen(EXIT)) == 0)
		// return (function_exit(command, data));
	return (EXIT_FAILURE);
}

int	ft_exec_command(t_command *command, t_shell *data)
{
	char *path;

	if (!data || !command)
		return (EXIT_FAILURE);
	path = ft_get_command_path(command->name, data->ev);
	if (!path)
	{
		ft_error_command_not_found(command->name);
		return (EXIT_COMMAND_NOT_FOUND); // TODO: check if it is the correct exit code
	}
	execve(path, command->args, data->ev);
	ft_printf(STDERR_FILENO, "Error: %s - %s\n", command->name, strerror(errno));
	free(path);
	return (EXIT_FAILURE);
}

static	bool	ft_handle_redirect_out(t_redirection *redirections)
{
	int	fd;

	if (!redirections)
		return (false);
	if (redirections->type == REDIRECT_OUT)
	{
		fd = open(redirections->target, O_WRONLY | O_CREAT | O_TRUNC,
				STANDARD_FILE_PERMISSIONS);
		if (fd < 0)
		{
			ft_printf(STDERR_FILENO, "minishell:  %s: %s\n", redirections->target, strerror(errno));
			return (false);
		}
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			close(fd);
			ft_printf(STDERR_FILENO, "minishell: error on dup2\n");
			return (false);
		}
		close(fd);
	}
	return (true);
}

static bool	ft_handle_append_out(t_redirection *redirections)
{
	int	fd;

	if (!redirections)
		return (false);
	if (redirections->type == APPEND_OUT)
	{
		fd = open(redirections->target, O_WRONLY | O_CREAT | O_APPEND,
				STANDARD_FILE_PERMISSIONS);
		if (fd < 0)
		{
			ft_printf(STDERR_FILENO, "minishell:  %s: %s\n", redirections->target, strerror(errno));
			return (false);
		}
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			close(fd);
			ft_printf(STDERR_FILENO, "minishell: error on dup2\n");
			return (false);
		}
		close(fd);
	}
	return (true);
}

// TODO: check exit program, maybe the redirection need to be reset in ft_handle_shell
bool	ft_apply_redirection(t_redirection *redirections)
{
	if (!redirections)
		return (false);
	while (redirections)
	{
		// if (redirections->type == REDIRECT_IN && !ft_handle_redirect_in(redirections))
		// 	return (false);
		// else if (redirections->type == REDIRECT_OUT && !ft_handle_redirect_out(redirections))
		if (redirections->type == REDIRECT_OUT && !ft_handle_redirect_out(redirections))
			return (false);
		else if (redirections->type == APPEND_OUT && !ft_handle_append_out(redirections))
			return (false);
		redirections = redirections->next;
	}
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
	return (true);
}


i would like to refactor all these codes because it starts to be too difficult to read, to follow, to maintain and to scale.
also i want to simplify the handle of all the redirection (when they are use alone, with command, with pipe, with logical operator or when there are a multiple mix of them all)!
currently they are done partially with ft_process_heredocs, then ft_exec_redirections, then later on with ft_setup_redirection and i am a bit lost with all these functions, if they are well linked with pipe or the standard fd

what would you suggest to do? can you give me the code to start the refactor?
