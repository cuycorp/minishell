/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 16:09:43 by mcamaren          #+#    #+#             */
/*   Updated: 2025/06/18 11:27:39 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_is_redirection_type(t_token_type type)
{
	return (type == TOKEN_REDIRECT_IN || type == TOKEN_REDIRECT_OUT
		|| type == TOKEN_HEREDOC || type == TOKEN_APPEND_OUT);
}

bool	ft_is_word_like_type(t_token_type type)
{
	return (type == TOKEN_WORD || type == TOKEN_DOUBLE_QUOTED_WORD
		|| type == TOKEN_SINGLE_QUOTED_WORD);
}

bool	ft_is_argument_type(t_token_type type)
{
	return (ft_is_word_like_type(type) || type == TOKEN_EXPANSION);
}

bool	ft_is_command_terminator(t_token_type type)
{
	return (type == TOKEN_PIPE || type == TOKEN_LOGICAL_AND
		|| type == TOKEN_LOGICAL_OR || type == TOKEN_PARENTHESIS_RIGHT
		|| type == TOKEN_END_OF_LINE || type == TOKEN_UNKNOWN);
}

// End of command if we have no more tokens OR we hit a command terminator
bool	ft_is_end_of_command(t_token **token_list)
{
	return (!(*token_list) || ft_is_command_terminator((*token_list)->type));
}

bool	ft_is_logical_operator(t_token_type type)
{
	return (type == TOKEN_LOGICAL_AND || type == TOKEN_LOGICAL_OR);
}
