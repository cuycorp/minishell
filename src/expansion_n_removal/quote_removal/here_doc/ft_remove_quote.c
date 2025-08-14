/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_quote.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamaren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 12:23:08 by mcamaren          #+#    #+#             */
/*   Updated: 2025/07/22 12:23:10 by mcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_append_nonquote_char(char *new, char c)
{
	char	*char_str;
	char	*tmp;

	char_str = ft_char_2_str(c);
	if (!char_str)
		return (free(new), NULL);
	tmp = new;
	new = ft_strjoin(new, char_str);
	free(tmp);
	free(char_str);
	if (!new)
		return (NULL);
	return (new);
}

char	*ft_remove_quote(char *str, char quote)
{
	int		i;
	char	*new;

	if (!str)
		return (NULL);
	new = ft_strdup("");
	if (!new)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] != quote)
		{
			new = ft_append_nonquote_char(new, str[i]);
			if (!new)
				return (NULL);
		}
		i++;
	}
	return (new);
}
