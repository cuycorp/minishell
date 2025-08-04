/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenize_mixed_word.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 11:08:10 by jgossard          #+#    #+#             */
/*   Updated: 2025/08/01 15:07:35 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Note on Double-Quoted String:
 * When you enclose characters in double quotes (`"`), Bash preserves the
 * literal value of most characters while allowing certain exceptions like
 * `$`, `\`, `!`, and special parameters like `*` and `@`.
 *
 * Key Points:
 * - `$` : Expands variables.
 * - `\` : Escapes special characters.
 * - `!` : Triggers history expansion (unless escaped).
 * - `*` and `@`: Expands positional parameters, but the behavior is slightly
 * 	different depending on the context.
 * - `"` : Can be included by escaping it with \"
 */

/**
 * @brief Advances the position pointer past a double-quoted string segment.
 *
 * Handles escaped double quotes (i.e., `\"`) inside the string. The position
 * pointer is moved forward until the closing unescaped double quote is found
 * or the end of the string is reached.
 *
 * Example: for input `"hello \"world\" test"`, the position will move past
 * the entire string.
 *
 * @param str   The input string.
 * @param pos   A pointer to the current position in the string; will be updated
 */
static void	ft_advance_past_double_quotes(char *str, unsigned int *pos)
{
	(*pos)++;
	while (str[*pos])
	{
		if (str[*pos] == '\\' && str[*pos + 1] == '"')
		{
			*pos += 2;
			continue ;
		}
		if (str[*pos] == '"')
		{
			(*pos)++;
			break ;
		}
		(*pos)++;
	}
}

static void	ft_advance_past_single_quotes(char *str, unsigned int *pos)
{
	(*pos)++;
	while (str[*pos] != '\'')
	{
		if (!str[*pos])
			break ;
		(*pos)++;
	}
	(*pos)++;
}

/**
 * @brief Determines the token type based on the presence of quotes.
 *
 * If the word includes at least one double-quoted segment, returns
 * `TOKEN_DOUBLE_QUOTED_WORD`, otherwise returns `TOKEN_WORD`.
 *
 * @param has_quote Boolean flag indicating whether quotes were found.
 * @return t_token_type The appropriate token type.
 */
static t_token_type	ft_get_token_type(bool has_double_quote,
		bool has_single_quote)
{
	if (has_double_quote && !has_single_quote)
		return (TOKEN_DOUBLE_QUOTED_WORD);
	else if (has_single_quote && !has_double_quote)
		return (TOKEN_SINGLE_QUOTED_WORD);
	else
		return (TOKEN_WORD);
}

/**
 * @brief Tokenizes a sequence of characters that may contain both quoted and unquoted parts.
 *
 * This function handles shell-like behavior where adjacent quoted and unquoted strings
 * form a single token (e.g., "hello"world → helloworld). It processes both unquoted
 * characters and double-quoted segments, and determines the appropriate token type based
 * on whether quotes were encountered.
 *
 * @param str   The full input string to tokenize.
 * @param pos   A pointer to the current position in the input string; will be updated.
 * @param data  Pointer to the shell state or token storage structure.
 */
void	ft_tokenize_mixed_word(char *str, unsigned int *pos, t_shell *data)
{
	t_token_type	token_type;
	unsigned int	start_index;
	bool			has_double_quote;
	bool			has_single_quote;

	if (!str || !data || !pos)
		return ;
	start_index = *pos;
	has_double_quote = false;
	has_single_quote = false;
	while (str[*pos])
	{
		if (str[*pos] == '\'')
		{
			has_single_quote = true;
			ft_advance_past_single_quotes(str, pos);
		}
		else if (str[*pos] == '"')
		{
			has_double_quote = true;
			ft_advance_past_double_quotes(str, pos);
		}
		else if (ft_is_special_operator(str[*pos]))
			break ;
		else if (ft_is_unquoted_char(str[*pos]))
			(*pos)++;
		else
			break ;
	}
	token_type = ft_get_token_type(has_double_quote, has_single_quote);
	ft_add_token_from_range(data, start_index, *pos, token_type);
}
