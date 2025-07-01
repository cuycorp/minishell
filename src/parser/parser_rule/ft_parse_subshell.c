/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_subshell.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 17:22:36 by jgossard          #+#    #+#             */
/*   Updated: 2025/07/01 20:41:50 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node	*ft_parse_subshell(t_token **tokens)
{
	t_ast_node	*node;

	if (!tokens)
		return (NULL);
	if (!ft_match_token(tokens, TOKEN_PARENTHESIS_LEFT))
	{
		ft_parse_error(*tokens, "expected '(' to start subshell");
		return (NULL);
	}
	if (!(*tokens))
		return (ft_parse_error(*tokens, "expected ')' to end subshell"), NULL);
	if (ft_is_command_terminator((*tokens)->type))
		return (ft_parse_error(*tokens, NULL), NULL);
	node = ft_parse_and_or_list(tokens);
	if (!node)
		return (NULL);
	if (!(*tokens) || !ft_match_token(tokens, TOKEN_PARENTHESIS_RIGHT))
	{
		ft_free_ast_tree(&node);
		ft_parse_error(*tokens, "expected ')' to end subshell");
		return (NULL);
	}
	return (node);
}
