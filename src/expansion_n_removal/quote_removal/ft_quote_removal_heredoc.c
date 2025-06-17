/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quote_removal_heredoc.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamaren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 11:31:15 by mcamaren          #+#    #+#             */
/*   Updated: 2025/07/01 11:31:17 by mcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_quote_2_str(char *str, int *i, char quote)
{
	char	*new;

	new = ft_strdup("");
	(*i) += 1;
	while (str[*i] != quote && str[*i])
	{
		new = ft_strjoin(new, ft_char_2_str(str[*i]));
		(*i)++;
	}
	(*i)++;
	return (new);
}

static char	*append_quoted_segment(char *final, char *str, int *i, char quote)
{
	char	*tmp;
	char	*to_str;

	tmp = final;
	to_str = ft_quote_2_str(str, i, quote);
	final = ft_strjoin(final, to_str);
	free(tmp);
	free(to_str);
	return (final);
}

static char	*append_unquoted_char(char *final, char c)
{
	char	*tmp;
	char	*to_str;

	tmp = final;
	to_str = ft_char_2_str(c);
	final = ft_strjoin(final, to_str);
	free(tmp);
	free(to_str);
	return (final);
}

char	*ft_handle_word_quotes(char *str)
{
	int		i;
	char	*final;

	i = 0;
	final = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '\'')
			final = append_quoted_segment(final, str, &i, '\'');
		else if (str[i] == '\"')
			final = append_quoted_segment(final, str, &i, '\"');
		else
			final = append_unquoted_char(final, str[i++]);
	}
	return (final);
}


char	*ft_expand_heredoc_delimiter(char *str, t_token_type type)
{
	if (type == TOKEN_DOUBLE_QUOTED_WORD)
		str = ft_remove_quote(str, '\"');
	else if (type == TOKEN_SINGLE_QUOTED_WORD)
		str = ft_remove_quote(str, '\'');
	else if (type == TOKEN_WORD)
		str = ft_handle_word_quotes(str);
	else
		str = ft_strdup(str);
	printf("expand heredoc delimiter %s\n", str);
	return (str);
}

