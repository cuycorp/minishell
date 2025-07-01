/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_subshell_group.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 10:04:25 by jgossard          #+#    #+#             */
/*   Updated: 2025/07/01 20:53:17 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node	*ft_parse_subshell_group(t_token **tokens)
{
	if (!tokens || !(*tokens))
		return (NULL);
	if ((*tokens)->type == TOKEN_PARENTHESIS_LEFT)
		return (ft_parse_subshell(tokens));
	return (ft_parse_pipeline(tokens));
}
