/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_interactive_ctrl_c.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamaren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:24:02 by mcamaren          #+#    #+#             */
/*   Updated: 2025/08/04 12:24:05 by mcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_close_heredocs_fd(t_ast_node *node)
{
	t_redirection	*redirection;

	if (!node)
		return ;
	if (node->type == AST_SIMPLE_COMMAND && node->command_data)
	{
		redirection = node->command_data->redirection;
		while (redirection)
		{
			if (redirection->type == HEREDOC && redirection->heredoc_fd != -1)
			{
				close(redirection->heredoc_fd);
				redirection->heredoc_fd = -1;
			}
			redirection = redirection->next;
		}
	}
	ft_close_heredocs_fd(node->left);
	ft_close_heredocs_fd(node->right);
}

static void	ft_reset_shell(t_shell *data)
{
	if (!data)
		return ;
	if (data->input)
	{
		free(data->input);
		data->input = NULL;
	}
	if (data->tokens_list)
		ft_free_tokens_list(&data->tokens_list);
	if (data->ast_root)
	{
		ft_close_heredocs_fd(data->ast_root);
		ft_free_ast_tree(&data->ast_root);
	}
}

bool	ft_interactive_ctrl_c(t_shell *data)
{
	if (!data->input)
		return (false);
	if (g_signal == 1 && ft_strncmp(data->input, "$?", ft_strlen("$?")) == 0)
	{
		data->exit_code = 130;
		ft_printf(STDERR_FILENO, "%d: command not found\n", data->exit_code);
		ft_reset_shell(data);
		g_signal = 0;
		return (true);
	}
	return (false);
}
