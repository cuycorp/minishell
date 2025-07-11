/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_apply_redirection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 15:56:37 by jgossard          #+#    #+#             */
/*   Updated: 2025/07/28 14:36:11 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO: delete this file


// static	bool	ft_handle_redirect_in(t_redirection *redirections)
// {
// 	int	fd;

// 	if (!redirections)
// 		return (false);
// 	if (redirections->type == REDIRECT_IN)
// 	{
// 		fd = open(redirections->target, O_RDONLY);
// 		if (fd < 0)
// 		{
// 			ft_printf(STDERR_FILENO, "minishell:  %s: %s\n", redirections->target, strerror(errno));
// 			return (false);
// 		}
// 		if (dup2(fd, STDIN_FILENO) == -1)
// 		{
// 			close(fd);
// 			ft_printf(STDERR_FILENO, "minishell: error on dup2\n");
// 			return (false);
// 		}
// 		close(fd);
// 	}
// 	return (true);
// }

// static	bool	ft_handle_redirect_out(t_redirection *redirections)
// {
// 	int	fd;

// 	if (!redirections)
// 		return (false);
// 	if (redirections->type == REDIRECT_OUT)
// 	{
// 		fd = open(redirections->target, O_WRONLY | O_CREAT | O_TRUNC,
// 				STANDARD_FILE_PERMISSIONS);
// 		if (fd < 0)
// 		{
// 			ft_printf(STDERR_FILENO, "minishell:  %s: %s\n", redirections->target, strerror(errno));
// 			return (false);
// 		}
// 		if (dup2(fd, STDOUT_FILENO) == -1)
// 		{
// 			close(fd);
// 			ft_printf(STDERR_FILENO, "minishell: error on dup2\n");
// 			return (false);
// 		}
// 		close(fd);
// 	}
// 	return (true);
// }

// static bool	ft_handle_append_out(t_redirection *redirections)
// {
// 	int	fd;

// 	if (!redirections)
// 		return (false);
// 	if (redirections->type == APPEND_OUT)
// 	{
// 		fd = open(redirections->target, O_WRONLY | O_CREAT | O_APPEND,
// 				STANDARD_FILE_PERMISSIONS);
// 		if (fd < 0)
// 		{
// 			ft_printf(STDERR_FILENO, "minishell:  %s: %s\n", redirections->target, strerror(errno));
// 			return (false);
// 		}
// 		if (dup2(fd, STDOUT_FILENO) == -1)
// 		{
// 			close(fd);
// 			ft_printf(STDERR_FILENO, "minishell: error on dup2\n");
// 			return (false);
// 		}
// 		close(fd);
// 	}
// 	return (true);
// }

// // TODO: check exit program, maybe the redirection need to be reset in ft_handle_shell
// bool	ft_apply_redirection(t_redirection *redirections)
// {
// 	if (!redirections)
// 		return (false);
// 	while (redirections)
// 	{
// 		// if (redirections->type == REDIRECT_IN && !ft_handle_redirect_in(redirections))
// 		// 	return (false);
// 		// else if (redirections->type == REDIRECT_OUT && !ft_handle_redirect_out(redirections))
// 		if (redirections->type == REDIRECT_OUT && !ft_handle_redirect_out(redirections))
// 			return (false);
// 		else if (redirections->type == APPEND_OUT && !ft_handle_append_out(redirections))
// 			return (false);
// 		redirections = redirections->next;
// 	}
// 	return (true);
// }
