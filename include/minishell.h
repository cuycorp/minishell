/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 13:39:32 by jgossard          #+#    #+#             */
/*   Updated: 2025/08/12 12:39:45 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/**
 * Required Functions and Headers
 */

/**
 * === BASIC I/O AND FILE OPERATIONS ===
 * - File descriptors: STDERR_FILENO, STDIN_FILENO, STDOUT_FILENO
 * - File operations: read, write, access, close, open, unlink
 * - Directory operations: chdir, getcwd, opendir, readdir, closedir
 * - File information: stat, lstat, fstat
 * === PIPE OPERATIONS ===
 * - Pipe creation: pipe
 * - Descriptor duplication: dup, dup2
 */
# include <unistd.h>	/* read, write, access, close, unlink, chdir,
							getcwd, execve, isatty, ttyname, ttyslot, pipe, dup,
							dup2, fork, STDERR_FILENO, STDIN_FILENO,
							STDOUT_FILENO */
# include <fcntl.h>		/* open, O_RDONLY, O_WRONLY,
							O_CREAT, O_TRUNC, O_APPEND */
# include <dirent.h>		/* opendir, readdir, closedir */
# include <sys/stat.h>	/* stat, lstat, fstat */
/**
 * === PROCESS CONTROL ===
 * - Process creation: fork, execve
 * - Process waiting: wait, waitpid, wait3, wait4
 * - Process types: pid_t
 */
# include <sys/types.h>	/* pid_t */
# include <sys/wait.h>	/* wait, waitpid, wait3, wait4 */
/**
 * === MEMORY AND STRING HANDLING ===
 * - Memory allocation: malloc, free
 * - String operations: strerror
 * - Standard I/O: printf, perror
 * - Exit functions: exit, EXIT_FAILURE, EXIT_SUCCESS
 * - Environment: getenv
 */
# include <stdbool.h>	/* bool type support */
# include <stdio.h>		/* printf, perror */
# include <stdlib.h>	//malloc, free, exit, EXIT_FAILURE, EXIT_SUCCESS, getenv
# include <string.h>	/* strerror */
/**
 * === SIGNAL HANDLING ===
 * - Signal operations: signal, sigaction, kill, sigemptyset, sigaddset
 */
# include <signal.h>	// signal, sigaction, kill, sigemptyset, sigaddset
/**
 * === TERMINAL I/O AND CONTROL ===
 * - Terminal information: isatty, ttyname, ttyslot, ioctl
 * - Terminal settings: tcsetattr, tcgetattr
 * - Terminal capabilities: tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
 */
# include <sys/ioctl.h>	/* ioctl */
# include <termios.h>	/* tcsetattr, tcgetattr */
# include <curses.h>	/* Terminal display functions: tgetent,
							tgetflag, tgetnum */
# include <term.h>		// Terminal capability functions: tgetstr, tgoto, tputs
/**
 * === LINE EDITING AND HISTORY ===
 * - Line reading: readline
 * - History: add_history
 * - Display control: rl_clear_history, rl_on_new_line, rl_replace_line,
 *  rl_redisplay
 */
# include <readline/readline.h> /* readline, rl_clear_history, rl_on_new_line,
									rl_replace_line, rl_redisplay */
# include <readline/history.h> /* add_history */
# include <linux/limits.h> /*max size of path PATH_MAX */
# include <limits.h> /*atoll*/

/* Personnal Libraries */
# include "ft_printf.h"
# include "get_next_line.h"
# include "libft.h"
/* Internal Headers*/
# include "structures.h"
# include "variables.h"
# include "expander.h"
# include "parser.h"
# include "exec.h"
# include "utils.h"
# include "signals.h"

/* FUNCTIONS */

/* INITIALIZER */

t_shell				*ft_init_shell(char **envp);
t_redirection		*ft_create_redirection(t_redirection_type type,
						char *target);
t_command			*ft_create_command(int argc);
t_exec_context		*ft_create_exec_context(t_ast_node *root);
t_wildcard_context	*ft_create_wildcard_context(const char *pattern);

/* ########  LEXER PART  ######## */

bool				ft_are_quotes_balanced(char *str);

/* Tokenize function */

void				ft_tokenize_word(char *str, unsigned int *pos,
						t_shell *data);
void				ft_tokenize_redirection(char *str, unsigned int *pos,
						t_shell *data);
void				ft_tokenize_parenthesis(char *str, unsigned int *pos,
						t_shell *data);
void				ft_tokenize_log_operator(char *str, unsigned int *pos,
						t_shell *data);
void				ft_tokenize_unknown(char *str, unsigned int *pos,
						t_shell *data);
void				ft_tokenize_mixed_word(char *str, unsigned int *pos,
						t_shell *data);
void				ft_tokenize_expansion(char *str, unsigned int *pos,
						t_shell *data);
void				ft_tokenize_end_of_line(unsigned int *pos, t_shell *data);
void				ft_tokenize_semicolon(char *str, unsigned int *pos,
						t_shell *data);

/* Token  function */

t_token				*ft_create_token(char *str, t_token_type type);
void				ft_add_token(t_token **tokens_list, t_token *new_token);
void				ft_add_token_from_range(t_shell *data, int start, int end,
						t_token_type type);
void				ft_free_tokens_list(t_token **tokens_list);
void				ft_print_tokens_list(t_shell *data);
void				ft_tokenizer(char *str, t_shell *data);

/* ########  BUILTINS  ######## */

int					function_cd(t_shell **data, t_command *command);
bool				ft_save_wd(char *variable);
char				*get_new_dir(int len, t_shell *data, t_command *command);
bool				ft_update_path(t_command *command, char *old_pwd, char *pwd,
						char *in_chdir);
int					function_pwd(t_shell *data, t_command *command);
int					function_echo(t_command *command);
bool				ft_validate_command(t_command *command,
						char *commmand_name);
int					function_export(t_command *command, t_shell *data);
char				*ft_set_var_definition(char *arguments, int *j,
						int *to_env);
bool				ft_is_valid_var_name(char *var_declaration, int *j);
bool				ft_print_export(t_shell *data);
bool				ft_evaluate_var_creation(t_command *command, t_shell *data);
bool				ft_replace_var_definition(char *new_var_definition,
						char **table);
bool				ft_var_definition_exists(char *var_definition,
						char **table);
bool				ft_is_same_var(char *var_name1, char *var_name2);
int					function_unset(t_command *command, t_shell *data);
bool				ft_unset_var(t_command *command, t_shell *data);
int					function_env(t_command *command, t_shell *data);
char				*ft_get_var_name(char *var_definition);
int					function_exit(t_command *command, t_shell *data);

/* ########  SHELL PART  ######## */

void				ft_handle_shell(t_shell *data);
void				ft_handle_history(char *str);
void				ft_handle_pipe(t_ast_node *root, t_shell *data);

#endif
