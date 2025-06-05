/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_pipeline.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 14:12:20 by jgossard          #+#    #+#             */
/*   Updated: 2025/06/19 13:57:01 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_parse_pipeline(t_token **token_list)
{
	if (!token_list || !(*token_list))
		return (false);
	if (!ft_parse_pipeline_command(token_list))
		return (ft_parse_error("expected command at start of pipeline"));
	while ((*token_list) && (*token_list)->type == TOKEN_PIPE)
	{
		ft_advance_token(token_list);
		if (!(*token_list))
			return (ft_parse_error("unexpected end of input after '|'"));
		if (ft_is_command_terminator((*token_list)->type))
			return (ft_parse_error("expected command after '|'"));
		if (!ft_parse_pipeline_command(token_list))
			return (ft_parse_error("expected command after '|'"));
	}
	return (true);
}
