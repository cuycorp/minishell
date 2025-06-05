/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_token_type.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 16:55:01 by jgossard          #+#    #+#             */
/*   Updated: 2025/06/09 18:11:58 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_get_word_token_type(t_token_type type)
{
	if (type == TOKEN_WORD)
		return ("TOKEN_WORD");
	if (type == TOKEN_DOUBLE_QUOTED_WORD)
		return ("TOKEN_DOUBLE_QUOTED_WORD");
	if (type == TOKEN_SINGLE_QUOTED_WORD)
		return ("TOKEN_SINGLE_QUOTED_WORD");
	return (NULL);
}

static char	*ft_get_redirection_token_type(t_token_type type)
{
	if (type == TOKEN_REDIRECT_IN)
		return ("TOKEN_REDIRECT_IN");
	if (type == TOKEN_REDIRECT_OUT)
		return ("TOKEN_REDIRECT_OUT");
	if (type == TOKEN_APPEND_OUT)
		return ("TOKEN_APPEND_OUT");
	if (type == TOKEN_HEREDOC)
		return ("TOKEN_HEREDOC");
	return (NULL);
}

char	*ft_stringify_token_type(t_token_type type)
{
	char	*result;

	result = ft_get_word_token_type(type);
	if (result)
		return (result);
	result = ft_get_redirection_token_type(type);
	if (result)
		return (result);
	if (type == TOKEN_PIPE)
		return ("TOKEN_PIPE");
	if (type == TOKEN_LOGICAL_AND)
		return ("TOKEN_LOGICAL_AND");
	if (type == TOKEN_LOGICAL_OR)
		return ("TOKEN_LOGICAL_OR");
	if (type == TOKEN_END_OF_LINE)
		return ("TOKEN_END_OF_LINE");
	if (type == TOKEN_PARENTHESIS_RIGHT)
		return ("TOKEN_PARENTHESIS_RIGHT");
	if (type == TOKEN_PARENTHESIS_LEFT)
		return ("TOKEN_PARENTHESIS_LEFT");
	if (type == TOKEN_EXPANSION)
		return ("TOKEN_EXPANSION");
	return ("TOKEN_UNKNOWN");
}
