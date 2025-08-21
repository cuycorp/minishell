/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 14:59:26 by jgossard          #+#    #+#             */
/*   Updated: 2025/08/21 10:44:20 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

/* ########  EXEC PART  ######## */

int		ft_run_command_tree(t_ast_node *root, t_shell *data);
int		ft_exec_node_recursive(t_ast_node *node, t_shell *data,
			t_exec_context *context);
int		ft_exec_simple_command(t_command *command, t_shell *data);
int		ft_exec_pipe_node(t_ast_node *root, t_shell *data);
int		ft_exec_redirections(t_redirection *redirection, t_shell *data);
int		ft_exec_heredoc(t_redirection *redirection, char *delimiter,
			t_shell *data);
int		ft_exec_logical_and(t_ast_node *node, t_shell *data,
			t_exec_context *context);
int		ft_exec_logical_or(t_ast_node *node, t_shell *data,
			t_exec_context *context);
int		ft_exec_external_command(t_command *command, t_shell *data);
int		ft_exec_child_builtin(t_command *command, t_shell *data);
int		ft_exec_parent_builtin(t_command *command, t_shell *data);

/* IO */

bool	ft_prepare_command_io(t_redirection *redirection,
			t_exec_context *context);
bool	ft_process_heredocs(t_ast_node *root, t_shell *data);
bool	ft_prepare_command_outputs(t_redirection *redirection,
			t_redirection *last_output, t_exec_context *context);
bool	ft_prepare_command_inputs(t_redirection *redirection,
			t_redirection *last_input, t_exec_context *context);

/* BUILTINS */

bool	ft_is_child_builtin(char *command_name);
bool	ft_is_parent_builtin(char *command_name);

/* ERRORS*/

void	ft_error_command_not_found(char *command_name, int exit_code,
			char *error_message);
void	ft_error_failed_to_fork(char *scope);
void	ft_error_failed_waitpid(char *scope);
void	ft_error_failed_to_pipe(char *scope);

/* UTILS */

/* Close FDS*/
void	ft_close_pipe_fds(int *pipe_fd);
void	ft_close_unused_heredocs(t_redirection *redirections,
			t_redirection *last_input);
void	ft_handle_dup2_and_close_fd(int oldfd, int newfd, t_shell *data);
void	ft_reset_context_fds(t_exec_context *context);

bool	ft_apply_dup2(int oldfd, int newfd);
int		ft_count_executable_nodes(t_ast_node *node);
bool	ft_wait_all_pids(t_exec_context *context);
void	ft_mark_pids_reaped(t_exec_context *context);
void	ft_exit_child(t_shell *data, int exit_code);
void	ft_reset_shell(t_shell *data);
char	*ft_get_command_path(char *command, char **envp, char **error_message);

#endif
