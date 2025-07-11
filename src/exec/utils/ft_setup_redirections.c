// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   ft_setup_redirections.c                            :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/07/11 15:36:23 by jgossard          #+#    #+#             */
// /*   Updated: 2025/07/27 22:10:28 by jgossard         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "minishell.h"

// // static t_redirection	*ft_get_last_input_redirection(t_redirection *redirection)
// // {
// // 	t_redirection	*last_input;
// // 	t_redirection	*current;

// // 	if (!redirection)
// // 		return (NULL);
// // 	current = redirection;
// // 	last_input = NULL;
// // 	while (current)
// // 	{
// // 		if (current->type == HEREDOC || current->type == REDIRECT_IN)
// // 			last_input = current;
// // 		current = current->next;
// // 	}
// // 	return (last_input);
// // }

// // static int	ft_exec_redirect_in(t_redirection *redirections)
// // {
// // 	int	fd;

// // 	if (!redirections)
// // 		return (-1);
// // 	fd = -1;
// // 	if (redirections->type == REDIRECT_IN)
// // 	{
// // 		fd = open(redirections->target, O_RDONLY);
// // 		if (fd < 0)
// // 		{
// // 			ft_printf(STDERR_FILENO, "minishell:  %s: %s\n", redirections->target, strerror(errno));
// // 			return (-1);
// // 		}
// // 	}
// // 	return (fd);
// // }

// // static bool	ft_handle_inputs(t_redirection *redirection, t_redirection *last_input, int *input_fd)
// // {
// // 	int	fd;

// // 	if (!redirection || !last_input || !input_fd)
// // 		return (false);
// // 	if (redirection->type == HEREDOC)
// // 	{
// // 		// fd = ft_exec_heredoc(redirection, redirection->target);
// // 		fd = redirection->heredoc_fd;
// // 		if (fd == -1)
// // 			return (false);
// // 		if (redirection == last_input)
// // 			*input_fd = fd;
// // 		else
// // 			close(fd);
// // 	}
// // 	else if (redirection->type == REDIRECT_IN)
// // 	{
// // 		int fd = ft_exec_redirect_in(redirection);
// // 		if (fd == -1)
// // 			return (false);
// // 		if (redirection == last_input)
// // 			*input_fd = fd;
// // 		else
// // 			close(fd);
// // 	}
// // 	return (true);
// // }

// // TODO: to delete
// bool	ft_setup_redirection(t_redirection *redirection)
// {
// 	// t_redirection	*last_input;
// 	int				input_fd;
// 	// int				output_fd;

// 	if (!redirection)
// 		return (true);
// 	dprintf(g_log,"ft_setup_redirection : enter function\n");
// 	// last_input = ft_get_last_input_redirection(redirection);
// 	input_fd = -1;
// 	// output_fd = -1;
// 	while (redirection)
// 	{
// 		// if (redirection->type == HEREDOC || redirection->type == REDIRECT_IN)
// 		// {
// 		// 	if (!ft_handle_inputs(redirection, last_input, &input_fd))
// 		// 		return (false);
// 		// }
// 		// else
// 		if (redirection->type == REDIRECT_OUT || redirection->type == APPEND_OUT)
// 		{
// 			if (!ft_apply_redirection(redirection))
// 				return (false);
// 		}
// 		redirection = redirection->next;
// 	}
// 	if (input_fd != -1)
// 	{
// 		if (dup2(input_fd, STDIN_FILENO) == -1)
// 		{
// 			close(input_fd);
// 			ft_putstr_fd("minishell: error on dup2 for heredoc\n", STDERR_FILENO);
// 			return (false);
// 		}
// 		close(input_fd);
// 	}
// 	dprintf(g_log,"ft_setup_redirection : exit function\n");
// 	return (true);
// }
