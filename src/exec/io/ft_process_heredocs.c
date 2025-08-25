/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_heredocs.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 12:29:45 by jgossard          #+#    #+#             */
/*   Updated: 2025/08/25 14:16:30 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	ft_handle_heredoc(t_redirection *redirection, t_shell *data)
{
	int	fd;

	while (redirection)
	{
		if (redirection->type == HEREDOC && redirection->heredoc_fd == -1)
		{
			if (data->last_redirection)
				ft_safe_close_and_reset_fd(&data->last_redirection->heredoc_fd);
			fd = ft_exec_heredoc(redirection, redirection->target, data);
			if (data->exit_code == 130)
				return (ft_safe_close_and_reset_fd(&fd), false);
			if (fd == -1)
			{
				ft_safe_close_and_reset_fd(&redirection->heredoc_fd);
				return (false);
			}
			ft_safe_close_and_reset_fd(&redirection->heredoc_fd);
			redirection->heredoc_fd = fd;
			data->last_redirection = redirection;
		}
		redirection = redirection->next;
	}
	return (true);
}

static bool	ft_process_node_heredoc(t_ast_node *node, t_shell *data)
{
	if (!node || !data)
		return (true);
	if (node->type == AST_REDIRECTION && node->redirection_data)
	{
		if (!ft_handle_heredoc(node->redirection_data, data))
			return (false);
	}
	if (node->type == AST_SIMPLE_COMMAND && node->command_data)
	{
		if (!ft_handle_heredoc(node->command_data->redirection, data))
			return (false);
	}
	return (true);
}

/**
 * @brief Processes heredocs in a given abstract syntax tree (AST) node.
 *
 * This function traverses the AST recursively to process all the heredocs
 * associated with simple commands. It checks each redirection in the command
 * and, if it's a heredoc with an unprocessed file descriptor, it executes the
 * heredoc by calling the helper function `ft_exec_heredoc()`. If successful,
 * the file descriptor is stored in the redirection's `heredoc_fd` field.
 *
 * @param root The root node of the AST to process. It represents a command or
 *             a structure containing commands and redirections.
 *
 * @return true if all heredocs were successfully processed; false otherwise.
 *         If any error occurs during heredoc processing or if the root is NULL,
 *         the function returns false.
 *
 * @note This function processes each node in the AST recursively, starting
 *       from the root. If any error occurs (such as a failed heredoc creation),
 *       the function will return false. If the root is NULL, the function
 *       returns true immediately since we can have command without heredocs.
 */
bool	ft_process_heredocs(t_ast_node *root, t_shell *data)
{
	bool	left_result;
	bool	right_result;

	if (!root || !data)
		return (true);
	left_result = true;
	right_result = true;
	if (!ft_process_node_heredoc(root, data))
		return (false);
	if (g_exit_code == 130)
		return (false);
	if (root->left)
	{
		left_result = ft_process_heredocs(root->left, data);
		if (!left_result)
			return (false);
	}
	if (root->right)
	{
		right_result = ft_process_heredocs(root->right, data);
		if (!right_result)
			return (false);
	}
	return (left_result && right_result);
}
