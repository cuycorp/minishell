/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenise_double_quote.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 11:08:10 by jgossard          #+#    #+#             */
/*   Updated: 2025/06/03 09:48:35 by jgossard         ###   ########.fr       */
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

static void	ft_handle_double_quoted_word_token(char *str, unsigned int *pos)
{
	(*pos)++;

	while (str[*pos])
	{
		if (str[*pos] == '\\' && str[*pos + 1] == '"')
		{
			*pos += 2;
			continue;
		}
		if (str[*pos] == '"')
		{
			(*pos)++;
			break;
		}
		(*pos)++;
	}
}

void	ft_tokenize_double_quote(char *str, unsigned int *pos, t_shell *data)
{
	int		start_index;

	if (!str)
		return ;
	start_index = *pos;
	ft_handle_double_quoted_word_token(str, pos);
	while (ft_is_unquoted_char(str[*pos]))
		(*pos)++;
	ft_add_token_from_range(data, start_index, *pos, TOKEN_DOUBLE_QUOTED_WORD);
}
