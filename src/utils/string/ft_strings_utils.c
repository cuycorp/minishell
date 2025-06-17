/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strings_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 14:27:13 by jgossard          #+#    #+#             */
/*   Updated: 2025/06/15 18:07:01 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_is_unquoted_char(char c)
{
	if (!ft_isprint(c))
		return (false);
	if (c == ' ' || c == '|' || c == '<' || c == '>' || c == '(' || c == ')' || c == '"'
		|| c == '\'' || c == '$' || c == '\\')
		return (false);
	return (true);
}

// TODO: unused function so far, to remove
bool	ft_is_double_quoted_char(char c)
{
	if (c == '\0' || c == '"')
		return (false);
	return (ft_isprint(c));
}

bool	ft_is_special_operator(char c)
{
	return (c == '|' || c == ';' || c == '&' || c == '<' || c == '>' || c == '('
		|| c == ')');
}

bool	ft_is_valid_expansion(char c)
{
	return ((c == '.' || c == '-' || c == '(' || c == ')' || c == '{'
			|| c == '}' || c == '\'' || c == '"' || c == '$'));
}
