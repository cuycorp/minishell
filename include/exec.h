/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 14:59:26 by jgossard          #+#    #+#             */
/*   Updated: 2025/08/04 23:33:37 by jgossard         ###   ########.fr       */
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
int		ft_exec_heredoc(t_redirection *redirections, char *delimiter, t_shell *data);
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

/* BUILTINS */

bool	ft_is_child_builtin(char *command_name);
bool	ft_is_parent_builtin(char *command_name);

/* ERRORS*/

void	ft_error_command_not_found(char *command_name);

/* UTILS */

bool	ft_apply_dup2(int oldfd, int newfd);
int		ft_count_executable_nodes(t_ast_node *node);
bool	ft_wait_all_pids(t_exec_context *context);
void	ft_mark_pids_reaped(t_exec_context *context);
void	ft_close_fds(int *pipe_fd);
void	ft_exit_child(t_shell *data, int exit_code);
void	ft_close_heredocs_fd(t_ast_node *node);
void	ft_reset_shell(t_shell *data);

#endif
