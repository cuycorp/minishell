/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_ast_node_type.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 16:11:02 by jgossard          #+#    #+#             */
/*   Updated: 2025/06/23 18:35:39 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node_type	ft_get_ast_node_type(t_token_type type)
{
	if (type == TOKEN_PIPE)
		return (AST_PIPE);
	if (type == TOKEN_LOGICAL_AND)
		return (AST_LOGICAL_AND);
	if (type == TOKEN_LOGICAL_OR)
		return (AST_LOGICAL_OR);
	return (AST_NONE);
}
