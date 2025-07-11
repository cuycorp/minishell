/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_logs_heredocs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 12:25:08 by jgossard          #+#    #+#             */
/*   Updated: 2025/07/28 14:36:27 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO: delete this file


// void	ft_log_heredocs(t_ast_node *node)
// {
// 	t_redirection	*redir;

// 	if (!node)
// 		return;
// 	if (node->type == AST_SIMPLE_COMMAND && node->command_data)
// 	{
// 		redir = node->command_data->redirection;
// 		while (redir)
// 		{
// 			if (redir->type == HEREDOC)
// 			{
// 				//TODO: remove the use of dprintf
// 				dprintf(g_log, "[HEREDOC] target: %s, fd: %d\n",
// 					redir->target,
// 					redir->heredoc_fd);
// 			}
// 			redir = redir->next;
// 		}
// 	}
// 	ft_log_heredocs(node->left);
// 	ft_log_heredocs(node->right);
// }
