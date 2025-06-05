/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_argument_or_redirection.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 15:25:38 by jgossard          #+#    #+#             */
/*   Updated: 2025/06/19 13:49:00 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_parse_argument_or_redirection(
	t_token **token_list, bool *has_redirection)
{
	if (!token_list)
		return (false);
	while (*token_list && !ft_is_end_of_command(token_list))
	{
		if (ft_is_argument_type((*token_list)->type))
		{
			if (!ft_parse_arguments(token_list))
				return (false);
		}
		else if (ft_is_redirection_type((*token_list)->type))
		{
			if (!ft_parse_redirection(token_list))
				return (false);
			*has_redirection = true;
		}
		else
			break;
	}
	return (true);
}
