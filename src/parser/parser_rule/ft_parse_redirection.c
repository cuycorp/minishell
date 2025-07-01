/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_redirection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 14:07:55 by jgossard          #+#    #+#             */
/*   Updated: 2025/07/01 19:29:33 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_redirection_type	ft_get_redirection_type(t_token_type type)
{
	if (type == TOKEN_REDIRECT_IN)
		return (REDIRECT_IN);
	if (type == TOKEN_REDIRECT_OUT)
		return (REDIRECT_OUT);
	if (type == TOKEN_APPEND_OUT)
		return (APPEND_OUT);
	if (type == TOKEN_HEREDOC)
		return (HEREDOC);
	return (UNKNOWN);
}

t_redirection	*ft_parse_redirection(t_token **tokens)
{
	t_redirection		*redirection;
	char				*target;
	t_redirection_type	type;

	if (!tokens || !(*tokens))
		return (NULL);
	if (!ft_is_redirection_type((*tokens)->type))
		return (NULL);
	type = ft_get_redirection_type((*tokens)->type);
	ft_advance_token(tokens);
	if (!(*tokens) || !ft_is_argument_type((*tokens)->type))
	{
		ft_parse_error(*tokens, "expected file/limiter after redirection");
		return (NULL);
	}
	target = ft_strdup((*tokens)->value);
	if (!target)
		return (NULL);
	ft_advance_token(tokens);
	redirection = ft_create_redirection(type, target);
	if (!redirection)
		return (free(target), NULL);
	free(target);
	target = NULL;
	return (redirection);
}
