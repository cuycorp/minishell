/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_and_or_list.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 10:17:22 by jgossard          #+#    #+#             */
/*   Updated: 2025/07/01 20:52:54 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	ft_handle_token_advance(t_token **tokens, t_ast_node *left)
{
	if ((*tokens)->next)
		ft_advance_token(tokens);
	else
	{
		ft_free_ast_tree(&left);
		ft_parse_error(*tokens, NULL);
		return (NULL);
	}
	return (true);
}

t_ast_node	*ft_parse_and_or_list(t_token **tokens)
{
	t_ast_node		*left;
	t_ast_node		*right;
	t_ast_node_type	logical_node;

	if (!tokens)
		return (NULL);
	left = ft_parse_subshell_group(tokens);
	if (!left)
		return (NULL);
	while (*tokens && ft_is_logical_operator((*tokens)->type))
	{
		logical_node = ft_get_ast_node_type((*tokens)->type);
		if (!ft_handle_token_advance(tokens, left))
			return (NULL);
		right = ft_parse_subshell_group(tokens);
		if (!right)
		{
			ft_free_ast_tree(&left);
			return (NULL);
		}
		left = ft_add_ast_node(logical_node, left, right);
		if (!left)
			return (ft_free_ast_tree(&right), NULL);
	}
	return (left);
}
