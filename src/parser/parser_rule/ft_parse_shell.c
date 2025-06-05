/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_shell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 11:30:31 by jgossard          #+#    #+#             */
/*   Updated: 2025/06/19 13:36:40 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_parse_shell(t_token **token_list)
{
	while ((*token_list))
	{
		if (!ft_parse_and_or_list(token_list))
			return (false);
		if (!(*token_list) || (*token_list)->type == TOKEN_END_OF_LINE)
			break ;
		if (ft_is_command_terminator((*token_list)->type) && !(*token_list)->next)
			return (false);
		ft_advance_token(token_list);
	}
	return (true);
}
