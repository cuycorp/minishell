/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_grouped_pipeline.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 17:22:36 by jgossard          #+#    #+#             */
/*   Updated: 2025/06/19 13:43:19 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_parse_grouped_pipeline(t_token **token_list)
{
	if (!token_list)
		return (false);
	if (!ft_match_token(token_list, TOKEN_PARENTHESIS_LEFT))
		return (ft_parse_error("expected '(' at start of grouped pipeline"));
	if (ft_is_command_terminator((*token_list)->type))
		return (ft_parse_error("invalid start inside grouped pipeline"));
	if (!ft_parse_and_or_list(token_list))
		return (ft_parse_error("invalid and_or_list inside grouped pipeline"));
	if (!(*token_list) || !ft_match_token(token_list, TOKEN_PARENTHESIS_RIGHT))
		return (ft_parse_error("expected ')' at end of grouped pipeline"));
	return (true);
}
