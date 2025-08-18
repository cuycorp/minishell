/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close_heredoc_fd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 11:16:21 by jgossard          #+#    #+#             */
/*   Updated: 2025/08/18 17:11:20 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_close_heredocs_fd(t_ast_node *node)
{
	t_redirection	*redirection;

	if (!node)
		return ;
	if (node->type == AST_SIMPLE_COMMAND && node->command_data)
	{
		redirection = node->command_data->redirection;
		while (redirection)
		{
			if (redirection->type == HEREDOC)
				ft_safe_close_and_reset_fd(&redirection->heredoc_fd);
			redirection = redirection->next;
		}
	}
	else if (node->type == AST_REDIRECTION && node->redirection_data)
	{
		redirection = node->redirection_data;
		while (redirection)
		{
			if (redirection->type == HEREDOC)
				ft_safe_close_and_reset_fd(&redirection->heredoc_fd);
			redirection = redirection->next;
		}
	}
	ft_close_heredocs_fd(node->left);
	ft_close_heredocs_fd(node->right);
}
