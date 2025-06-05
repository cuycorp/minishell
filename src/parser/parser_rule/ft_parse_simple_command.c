/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_simple_command.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 14:07:13 by jgossard          #+#    #+#             */
/*   Updated: 2025/06/19 13:50:23 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_parse_simple_command(t_token **token_list)
{
	bool has_command;
	bool has_redirection;

	if (!token_list || !(*token_list))
		return (false);
	has_command = false;
	has_redirection = false;
	while ((*token_list) && ft_is_redirection_type((*token_list)->type))
	{
		if (!ft_parse_redirection(token_list))
			return (ft_parse_error("invalid redirection"));
		has_redirection = true;
	}
	if (*token_list && ft_is_argument_type((*token_list)->type))
	{
		if (!ft_parse_command_word(token_list))
			return (ft_parse_error("invalid command word"));
		has_command = true;
	}
	if (!ft_parse_argument_or_redirection(token_list, &has_redirection))
		return (false);
	if (!has_command && !has_redirection)
		return (ft_parse_error("missing command or redirection"));
	return (true);
}
