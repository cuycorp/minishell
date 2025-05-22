/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 13:39:32 by jgossard          #+#    #+#             */
/*   Updated: 2025/05/22 14:47:01 by jgossard         ###   ########.fr       */
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
# include <sys/wait.h>	/* wait, waitpid, wait3, wait4 */
# include <sys/types.h>	/* pid_t */
/**
 * === MEMORY AND STRING HANDLING ===
 * - Memory allocation: malloc, free
 * - String operations: strerror
 * - Standard I/O: printf, perror
 * - Exit functions: exit, EXIT_FAILURE, EXIT_SUCCESS
 * - Environment: getenv
 */
# include <stdio.h>		/* printf, perror */
# include <stdlib.h>	//malloc, free, exit, EXIT_FAILURE, EXIT_SUCCESS, getenv
# include <string.h>	/* strerror */
# include <stdbool.h>	/* bool type support */
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
# include <readline/readline.h>	/* readline, rl_clear_history, rl_on_new_line,
									rl_replace_line, rl_redisplay */
# include <readline/history.h>	/* add_history */
/* Personnal Libraries */
# include "libft.h"
# include "get_next_line.h"
# include "ft_printf.h"
/* Internal Headers*/
# include "structures.h"
# include "utils.h"

/* MACRO */

# define EXIT "exit"
/* FUNCTIONS */

void	ft_handle_shell(t_shell *data);
void	ft_handle_history(char *str);

#endif
