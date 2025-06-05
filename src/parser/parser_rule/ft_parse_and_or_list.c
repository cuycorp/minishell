/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_and_or_list.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 10:17:22 by jgossard          #+#    #+#             */
/*   Updated: 2025/06/19 13:40:24 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_parse_and_or_list(t_token **token_list)
{
	if (!token_list)
		return (false);
	if (!ft_parse_pipeline_group(token_list))
		return (false);
	while (*token_list && ft_is_logical_operator((*token_list)->type))
	{
		ft_advance_token(token_list);
		if (!(*token_list))
			return (ft_parse_error(
				"unexpected end of input after logical operator"));
		if (!ft_parse_pipeline_group(token_list))
			return (ft_parse_error(
				"expected pipeline/grouped_pipeline after logical operator"));
	}
	return (true);
}
