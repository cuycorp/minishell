/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 10:58:22 by jgossard          #+#    #+#             */
/*   Updated: 2025/06/19 13:54:08 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_advance_token(t_token **token_list)
{
	if (*token_list)
		*token_list = (*token_list)->next;
}

bool	ft_parse_error(const char *msg)
{
	if (msg)
		ft_printf(STDERR_FILENO, "Error: %s\n", msg);
	return (false);
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
 * @param[in,out] token_list A double pointer to the current token in the
 * token list.This pointer is updated to point to the next token
 * if a match occurs.
 * @param[in] expected The expected token type to match against
 * the current token.
 *
 * @return true if the current token matches the expected type
 * and the pointer was advanced;false otherwise.
 */
bool	ft_match_token(t_token **token_list, t_token_type expected)
{
	if (*token_list && (*token_list)->type == expected)
	{
		ft_advance_token(token_list);
		return (true);
	}
	return (false);
}

