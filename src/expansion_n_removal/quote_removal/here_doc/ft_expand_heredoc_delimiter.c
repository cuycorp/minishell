/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_heredoc_delimiter.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 11:31:15 by mcamaren          #+#    #+#             */
/*   Updated: 2025/07/09 11:18:55 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_expand_heredoc_delimiter(char *str, t_token_type type)
{
	if (!str)
		return (NULL);
	if (type == TOKEN_DOUBLE_QUOTED_WORD)
		str = ft_remove_quote(str, '\"');
	else if (type == TOKEN_SINGLE_QUOTED_WORD)
		str = ft_remove_quote(str, '\'');
	else if (type == TOKEN_WORD || type == TOKEN_EXPANSION)
		str = ft_remove_quotes_of_token_word(str);
	else
		str = ft_strdup(str);
	if (!str)
		return (NULL);
	return (str);
}
