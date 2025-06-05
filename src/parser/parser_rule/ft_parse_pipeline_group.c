/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_pipeline_group.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 10:04:25 by jgossard          #+#    #+#             */
/*   Updated: 2025/06/19 13:41:26 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_parse_pipeline_group(t_token **token_list)
{
	if (!token_list || !(*token_list))
		return (false);
	if ((*token_list)->type == TOKEN_PARENTHESIS_LEFT)
		return (ft_parse_grouped_pipeline(token_list));
	return (ft_parse_pipeline(token_list));
}
