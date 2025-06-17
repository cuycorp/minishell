/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_expanded_variables.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamaren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 13:59:24 by mcamaren          #+#    #+#             */
/*   Updated: 2025/07/22 13:59:29 by mcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



static char	*ft_append_char(char *str, char c)
{
	char	*final;
	char	*char_str;

	if (!str)
		return (NULL);
	char_str = ft_char_2_str(c);
	if (!char_str)
		return (NULL);
	final = ft_strjoin(str, char_str);
	free(char_str);
	if (!final)
		return (free(str), NULL);
	return (free(str), final);
}

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
		if (str[i] == '$' && str[i + 1])
			final = ft_handle_dollar_cases(str, &i, final, data);
		else if (str[i] == '\'' && str[i + 1])
			final = ft_handle_single_quotes(str, &i, final);
		else
			final = ft_append_char(final, str[i++]);
		if (!final)
			return (NULL);
	}
	return (final);
}


