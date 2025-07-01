/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 10:58:22 by jgossard          #+#    #+#             */
/*   Updated: 2025/07/01 19:59:02 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_advance_token(t_token **tokens)
{
	if (*tokens)
		*tokens = (*tokens)->next;
}

void	ft_parse_error(const t_token *token, const char *msg)
{
	char	*template;

	template = "minishell: syntax error near unexpected token";
	if (token && token->type == TOKEN_END_OF_LINE)
		ft_printf(STDERR_FILENO,
			"minishell: syntax error near unexpected token `newline'\n");
	else if (token && token->value && msg)
		ft_printf(STDERR_FILENO, "%s '%s', %s\n", template, token->value, msg);
	else if (token && token->value)
		ft_printf(STDERR_FILENO, "%s '%s'\n", template, token->value);
	else if (msg)
		ft_printf(STDERR_FILENO, "minishell: syntax error, %s\n", msg);
}

/**
 * @brief	Matches the current token against an expected type
 * 			and advances if matched.
 *
 * This function checks whether the current token in the token list matches
 * the specified expected token type. If the match is successful, the token
 * pointer is advanced to the next token in the list
 * and the function returns true. If the match fails, the token pointer remains
 * unchanged and the function returns false.
 *
 * @param[in,out] tokens A double pointer to the current token in the
 * token list.This pointer is updated to point to the next token
 * if a match occurs.
 * @param[in] expected The expected token type to match against
 * the current token.
 *
 * @return true if the current token matches the expected type
 * and the pointer was advanced;false otherwise.
 */
bool	ft_match_token(t_token **tokens, t_token_type expected)
{
	if (*tokens && (*tokens)->type == expected)
	{
		ft_advance_token(tokens);
		return (true);
	}
	return (false);
}
