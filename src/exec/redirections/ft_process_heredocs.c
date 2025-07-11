/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_heredocs.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 12:29:45 by jgossard          #+#    #+#             */
/*   Updated: 2025/07/25 12:32:26 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO: renamed it to something like ft_prepare_heredoc
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
 *       returns true immediately.
 */
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
