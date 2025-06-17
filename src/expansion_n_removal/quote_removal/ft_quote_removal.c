/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quote_removal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamaren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 11:20:58 by mcamaren          #+#    #+#             */
/*   Updated: 2025/07/01 11:21:02 by mcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_char_2_str(char c)
{
	char *result;

	result = ft_alloc_struct(2 * sizeof(char));
	result[0] = c;
	result[1] = '\0';
	return (result);
}

char	*ft_remove_quote(char *str, char quote)
{
	int		i;
	char	*new;
	char	*tmp;
	char *char_str;

	new = ft_strdup("");
	i = 0;
	while (str[i])
	{
		if (str[i] != quote)
		{
			char_str = ft_char_2_str(str[i]);
			tmp = new;
			new = ft_strjoin(new, char_str);
			free(tmp);
			free(char_str);
		}
		i++;
	}
	return (new);
}

int	ft_is_valid_token_heredoc(t_token_type type)
{
	if (type == TOKEN_DOUBLE_QUOTED_WORD || type == TOKEN_SINGLE_QUOTED_WORD
		|| type == TOKEN_WORD || type == TOKEN_EXPANSION)
		return (1);
	return (0);
}


int	ft_quote_removal(t_token **token_list)
{
	t_token	*current;

	current = *token_list;
	while (current)
	{
		if (current->type == TOKEN_HEREDOC && current->next
			&& ft_is_valid_token_heredoc(current->next->type))
		{
			current->next->value = ft_expand_heredoc_delimiter(current->next->value,
					current->next->type);
			current = current->next->next;
		}
		else
		{
			if (current->type == TOKEN_DOUBLE_QUOTED_WORD)
				current->value = ft_remove_quote(current->value, '\"');
			if (current->type == TOKEN_SINGLE_QUOTED_WORD)
				current->value = ft_remove_quote(current->value, '\'');
			if (current->type == TOKEN_WORD)
				current->value = ft_handle_word_quotes(current->value);
			current = current->next;
		}
	}
	return (0);
}
