/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_pipeline_command.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:09:20 by jgossard          #+#    #+#             */
/*   Updated: 2025/06/19 13:43:25 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_parse_pipeline_command(t_token **tokens)
{
	if (!*tokens)
		return (false);
	if ((*tokens)->type == TOKEN_PARENTHESIS_LEFT)
		return (ft_parse_grouped_pipeline(tokens));
	return (ft_parse_simple_command(tokens));
}
