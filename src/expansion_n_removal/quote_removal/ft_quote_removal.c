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

static bool	ft_process_regular_token(t_token *token)
{
	char	*tmp;

	tmp = token->value;
	if (token->type == TOKEN_DOUBLE_QUOTED_WORD)
		token->value = ft_remove_quote(tmp, '\"');
	else if (token->type == TOKEN_SINGLE_QUOTED_WORD)
		token->value = ft_remove_quote(tmp, '\'');
	else if (token->type == TOKEN_WORD)
		token->value = ft_remove_quotes_of_token_word(tmp);
	if (token->type == TOKEN_DOUBLE_QUOTED_WORD
		|| token->type == TOKEN_SINGLE_QUOTED_WORD || token->type == TOKEN_WORD)
		free(tmp);
	if (!token->value)
		return (false);
	return (true);
}

static bool	ft_process_heredoc_token(t_token **current)
{
	char	*tmp;

	if (!(*current)->next)
		return (perror("zsh: parse error near \n"), false);
	if (!ft_is_valid_delimiter_token((*current)->next->type))
		return (perror("zsh: parse error near"), false);
	tmp = (*current)->next->value;
	(*current)->next->value = ft_expand_heredoc_delimiter(tmp,
			(*current)->next->type);
	free(tmp);
	if (!(*current)->next->value)
		return (false);
	*current = (*current)->next->next;
	return (true);
}

bool	ft_quote_removal(t_token **token_list, t_shell *data)
{
	t_token	*current;

	(void)data;
	if (!*token_list)
		return (false);
	current = *token_list;
	while (current)
	{
		if (current->type == TOKEN_HEREDOC)
		{
			if (!ft_process_heredoc_token(&current))
				return (false);
		}
		else
		{
			if (!ft_process_regular_token(current))
				return (false);
			current = current->next;
		}
	}
	return (true);
}
