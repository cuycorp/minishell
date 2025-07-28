/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 14:59:26 by jgossard          #+#    #+#             */
/*   Updated: 2025/07/28 20:11:46 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

int		ft_executor(t_ast_node *root, t_shell *data);

/* ########  EXEC PART  ######## */

int		ft_exec_logical_and(t_ast_node *node, t_shell *data,
			t_exec_context *context);
int		ft_exec_logical_or(t_ast_node *node, t_shell *data,
			t_exec_context *context);
int		ft_exec_command(t_command *command, t_shell *data);
int		ft_exec_simple_command(t_command *command, t_shell *data,
			t_exec_context *context);
int		ft_exec_redirections(t_redirection *redirection, t_exec_context *context);
int		ft_exec_child_builtin(t_command *command, t_shell *data);
int		ft_exec_parent_builtin(t_command *command, t_shell *data);
int		ft_exec_pipe_node(t_ast_node *root, t_shell *data,
			t_exec_context *context);
int		ft_exec_heredoc(t_redirection *redirections, char *delimiter);
int		ft_execute_ast_tree(t_ast_node *node, t_shell *data,
			t_exec_context *context);

/* IO */

bool	ft_prepare_command_io(t_redirection *redirection,
			t_exec_context *context);
bool	ft_process_heredocs(t_ast_node *root);
// bool	ft_prepare_inputs(t_redirection *redirection, t_redirection *last_input,
// 		int *input_fd);
// bool	ft_prepare_outputs(t_redirection *redirection, int *output_fd);

/* BUILTINS */
bool	ft_is_builtin_function(char *command_name);
bool	ft_is_parent_builtins(char *command_name);

/* UTILS */

bool	ft_apply_dup2(int oldfd, int newfd);
int		ft_count_cmd_nodes(t_ast_node *node);
int		ft_wait_all_pids(t_shell *data, t_exec_context *context);
void	ft_log_heredocs(t_ast_node *node); // TODO: to keep?
void	ft_close_fd_if_open(int *fd);

#endif
