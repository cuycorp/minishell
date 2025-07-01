/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_redirection_node.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 14:17:43 by jgossard          #+#    #+#             */
/*   Updated: 2025/06/30 10:08:25 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node	*ft_create_redirection_node(t_redirection *redirection)
{
	t_ast_node	*node;

	node = ft_alloc_struct(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = AST_REDIRECTION;
	node->redirection_data = redirection;
	node->command_data = NULL;
	return (node);
}
