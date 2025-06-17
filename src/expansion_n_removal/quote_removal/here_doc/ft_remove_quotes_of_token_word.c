/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_quotes_of_token_word.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamaren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 12:23:26 by mcamaren          #+#    #+#             */
/*   Updated: 2025/07/22 12:23:31 by mcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static char	*ft_quote_2_str(char *str, int *i, char quote)
{
	char	*new;
	char	*character;
	char	*tmp;

	if (!str)
		return (NULL);
	new = ft_strdup("");
	if (!new)
		return (NULL);
	(*i) += 1;
	while (str[*i] != quote && str[*i])
	{
		character = ft_char_2_str(str[*i]);
		if (!character)
			return (free(new), NULL);
		tmp = new;
		new = ft_strjoin(new, character);
		free(tmp);
		free(character);
		if (!new)
			return (NULL);
		(*i)++;
	}
	(*i)++;
	return (new);
}

static char	*append_quoted_segment(char *final, char *str, int *i, char quote)
{
	char	*result;
	char	*to_str;

	if (!final || !str)
		return (NULL);
	to_str = ft_quote_2_str(str, i, quote);
	if (!to_str)
		return (free(final), NULL);
	result = ft_strjoin(final, to_str);
	free(to_str);
	if (!result)
		return (free(final), NULL);
	return (free(final), result);
}


static char	*append_unquoted_char(char *final, char c)
{
	char	*to_str;
	char	*result;

	if (!final)
		return (NULL);
	to_str = ft_char_2_str(c);
	if (!to_str)
		return (free(final), NULL);
	result = ft_strjoin(final, to_str);
	free(to_str);
	if (!result)
		return (free(final), NULL);
	return (free(final), result);
}


char	*ft_remove_quotes_of_token_word(char *str)
{
	int		i;
	char	*final;

	if (!str)
		return (NULL);
	i = 0;
	final = ft_strdup("");
	if (!final)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '\'')
			final = append_quoted_segment(final, str, &i, '\'');
		else if (str[i] == '\"')
			final = append_quoted_segment(final, str, &i, '\"');
		else
			final = append_unquoted_char(final, str[i++]);
		if (!final)
			return (NULL);
	}
	return (final);
}
