/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_expanded_variables.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 13:59:24 by mcamaren          #+#    #+#             */
/*   Updated: 2025/08/19 18:18:48 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_handle_single_quotes(char *str, int *i, char *final)
{
	char	*single;
	char	*tmp;

	single = ft_extract_single_quoted_str(str, i);
	if (!single)
		return (NULL);
	tmp = final;
	final = ft_strjoin(final, single);
	free(tmp);
	free(single);
	if (!final)
		return (NULL);
	return (final);
}

static bool	ft_is_quote(char c)
{
	if (c == '"' || c == '\'')
		return (true);
	return (false);
}

static char	*ft_expand_next(char *str, int *i, char *final, t_shell *data)
{
	if (str[*i] == '$' && str[*i + 1]
		&& ft_is_valid_expansion_start(str[*i + 1]))
		final = ft_handle_dollar_cases(str, i, final, data);
	else if (str[*i] == '$' && str[*i + 1] && ft_is_quote(str[*i + 1]))
		(*i)++;
	else if (str[*i] == '\'' && str[*i + 1])
		final = ft_handle_single_quotes(str, i, final);
	else if (str[*i] == '\"' && str[*i + 1])
		final = ft_handle_double_quotes(str, i, final, data);
	else
		final = ft_append_char(final, str[(*i)++]);
	return (final);
}

char	*ft_fill_expanded_variables(char *str, t_shell *data)
{
	int		i;
	char	*final;

	if (!str || !data)
		return (NULL);
	i = 0;
	final = ft_strdup("");
	if (!final)
		return (NULL);
	while (str[i])
	{
		final = ft_expand_next(str, &i, final, data);
		if (!final)
			return (NULL);
	}
	return (final);
}
