/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_simple_command.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 14:07:13 by jgossard          #+#    #+#             */
/*   Updated: 2025/08/22 14:53:23 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_cleanup_on_error(t_command *command, t_redirection **redir_list)
{
	if (command)
		ft_free_command(command);
	if (redir_list && *redir_list)
		ft_free_redirection(redir_list);
}

static t_ast_node	*ft_create_final_node(t_command *cmd,
		t_redirection *redir_list, bool has_cmd, bool has_redir)
{
	if (!has_cmd && has_redir)
		return (ft_create_redirection_node(redir_list));
	if (has_cmd && cmd)
	{
		if (has_redir)
			cmd->redirection = redir_list;
		return (ft_create_simple_command_node(cmd));
	}
	return (NULL);
}

static bool	ft_parse_remaining_args(t_token **tokens, t_command *command,
	bool *has_command)
{
	if (!tokens || !command || !has_command)
		return (false);
	if (command && *tokens && ft_is_argument_type((*tokens)->type))
	{
		if (!ft_append_remaining_arguments(command, tokens, has_command))
			return (false);
	}
	return (true);
}

static t_ast_node	*ft_build_ast_tree_from_tokens(t_token **tokens)
{
	t_command		*command;
	t_redirection	*redirections;
	bool			has_command;
	bool			has_redir;
	t_ast_node		*node;

	if (!tokens || !(*tokens))
		return (NULL);
	has_command = false;
	has_redir = false;
	redirections = NULL;
	if (!ft_extract_redirections(&redirections, tokens, &has_redir))
		return (NULL);
	command = ft_create_and_fill_command(tokens, &has_command);
	if (!ft_extract_redirections(&redirections, tokens, &has_redir))
		return (ft_free_command(command), NULL);
	if (command && *tokens && ft_is_argument_type((*tokens)->type))
	{
		if (!ft_parse_remaining_args(tokens, command, &has_command))
			return (ft_free_redir_and_command(&redirections, command), NULL);
	}
	node = ft_create_final_node(command, redirections, has_command, has_redir);
	if (!node)
		ft_cleanup_on_error(command, &redirections);
	return (node);
}

t_ast_node	*ft_parse_simple_command(t_token **tokens)
{
	if (!tokens || !(*tokens))
		return (NULL);
	return (ft_build_ast_tree_from_tokens(tokens));
}
