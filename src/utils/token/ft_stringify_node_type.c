/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stringify_node_type.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 12:27:39 by jgossard          #+#    #+#             */
/*   Updated: 2025/08/19 12:31:50 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_stringify_node_type(t_ast_node_type type)
{
	if (type == AST_PIPE)
		return ("AST_PIPE");
	if (type == AST_REDIRECTION)
		return ("AST_REDIRECTION");
	if (type == AST_SIMPLE_COMMAND)
		return ("AST_SIMPLE_COMMAND");
	if (type == AST_LOGICAL_AND)
		return ("AST_LOGICAL_AND");
	if (type == AST_LOGICAL_OR)
		return ("AST_LOGICAL_OR");
	return (NULL);
}
