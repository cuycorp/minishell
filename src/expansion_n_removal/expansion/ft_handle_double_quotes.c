/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_double_quotes.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 18:34:48 by mcamaren          #+#    #+#             */
/*   Updated: 2025/08/19 18:18:48 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_len_double_quoted_section(char *str, int *i)
{
	int	len;
	int	start;

	if (!str || !i)
		return (-1);
	start = *i;
	(*i)++;
	while (str[*i])
	{
		if (str[*i] == '"')
		{
			(*i)++;
			break ;
		}
		(*i)++;
	}
	len = *i - start;
	return (len);
}

static char	*ft_extract_double_quoted_str(char *str, int *i)
{
	int		len;
	int		start;
	char	*doubleq;

	if (!str || !i)
		return (NULL);
	start = *i;
	len = ft_len_double_quoted_section(str, i);
	doubleq = ft_substr(str, start, len);
	if (!doubleq)
		return (NULL);
	return (doubleq);
}

static char	*ft_expand_double_quoted(char *double_quotes, t_shell *data)
{
	char	*new_dq;
	int		i;

	i = 0;
	if (!double_quotes || !data)
		return (NULL);
	new_dq = ft_strdup("");
	if (!new_dq)
		return (free(double_quotes), NULL);
	while (double_quotes[i])
	{
		if (double_quotes[i] == '$' && double_quotes[i + 1]
			&& ft_is_valid_expansion_start(double_quotes[i + 1]))
			new_dq = ft_handle_dollar_cases(double_quotes, &i, new_dq, data);
		else
			new_dq = ft_append_char(new_dq, double_quotes[i++]);
		if (!new_dq)
			return (free(double_quotes), NULL);
	}
	return (free(double_quotes), new_dq);
}

char	*ft_handle_double_quotes(char *str, int *i, char *final, t_shell *data)
{
	char	*doublequote;
	char	*tmp;

	if (!str || !i || !final || !data)
		return (NULL);
	doublequote = ft_extract_double_quoted_str(str, i);
	if (!doublequote)
		return (NULL);
	doublequote = ft_expand_double_quoted(doublequote, data);
	if (!doublequote)
		return (NULL);
	tmp = final;
	final = ft_strjoin(final, doublequote);
	free(tmp);
	free(doublequote);
	if (!final)
		return (NULL);
	return (final);
}
