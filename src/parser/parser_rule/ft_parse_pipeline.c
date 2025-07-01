/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_pipeline.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 14:12:20 by jgossard          #+#    #+#             */
/*   Updated: 2025/07/01 20:22:28 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	ft_handle_token_advance_and_check_terminator(t_token **tokens,
		t_ast_node **left)
{
	if ((*tokens)->next)
		ft_advance_token(tokens);
	else
	{
		ft_free_ast_tree(left);
		ft_parse_error(*tokens, NULL);
		return (false);
	}
	if (ft_is_command_terminator((*tokens)->type))
	{
		ft_free_ast_tree(left);
		ft_parse_error(*tokens, NULL);
		return (false);
	}
	return (true);
}
t_ast_node	*ft_parse_pipeline(t_token **tokens)
{
	t_ast_node		*left;
	t_ast_node		*right;
	t_ast_node_type	operator;

	if (!tokens || !(*tokens))
		return (NULL);
	left = ft_parse_pipeline_command(tokens);
	if (!left)
		return (ft_parse_error(*tokens, NULL), NULL);
	while ((*tokens) && (*tokens)->type == TOKEN_PIPE)
	{
		operator= ft_get_ast_node_type((*tokens)->type);
		if (!ft_handle_token_advance_and_check_terminator(tokens, &left))
			return (NULL);
		right = ft_parse_pipeline_command(tokens);
		if (!right)
			return (ft_free_ast_tree(&left), NULL);
		left = ft_add_ast_node(operator, left, right);
		if (!left)
			return (ft_free_ast_tree(&right), NULL);
	}
	return (left);
}
