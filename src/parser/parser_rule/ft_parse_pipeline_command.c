/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_pipeline_command.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:09:20 by jgossard          #+#    #+#             */
/*   Updated: 2025/08/01 15:30:48 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node	*ft_parse_pipeline_command(t_token **tokens)
{
	if (!tokens || !*tokens)
		return (NULL);
	if ((*tokens)->type == TOKEN_PARENTHESIS_LEFT)
		return (ft_parse_subshell(tokens));
	return (ft_parse_simple_command(tokens));
}
