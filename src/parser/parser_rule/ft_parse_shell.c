/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_shell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 11:30:31 by jgossard          #+#    #+#             */
/*   Updated: 2025/07/01 20:44:56 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	ft_check_for_end_of_input(t_token **tokens, t_ast_node **left)
{
	if (!(*tokens)->next)
	{
		ft_free_ast_tree(left);
		ft_parse_error(*tokens, NULL);
		return (false);
	}
	return (true);
}

t_ast_node	*ft_parse_shell(t_token **tokens)
{
	t_ast_node		*left;
	t_ast_node		*right;
	t_ast_node_type	operator;

	if (!tokens || !(*tokens))
		return (NULL);
	left = ft_parse_and_or_list(tokens);
	if (!left)
		return (NULL);
	while ((*tokens) && ft_is_command_terminator((*tokens)->type))
	{
		if ((*tokens)->type == TOKEN_END_OF_LINE)
			break ;
		if (!ft_check_for_end_of_input(tokens, &left))
			return (NULL);
		operator = ft_get_ast_node_type((*tokens)->type);
		ft_advance_token(tokens);
		right = ft_parse_and_or_list(tokens);
		if (!right)
			return (ft_free_ast_tree(&left), NULL);
		left = ft_add_ast_node(operator, left, right);
		if (!left)
			return (ft_free_ast_tree(&right), NULL);
	}
	return (left);
}
