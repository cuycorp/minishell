/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace_current_token_with_matches.c            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 00:22:11 by jgossard          #+#    #+#             */
/*   Updated: 2025/08/13 15:43:36 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_free_token_list(t_token *token)
{
	t_token	*next;

	while (token)
	{
		next = token->next;
		free(token->value);
		free(token);
		token = next;
	}
}

static bool	ft_update_first_token_value(t_token *current, char *match,
	char **matches)
{
	if (!current || !match)
		return (false);
	free(current->value);
	current->value = ft_strdup(match);
	if (!current->value)
	{
		ft_free_char_tab(matches);
		return (false);
	}
	return (true);
}

static bool	ft_handle_insert_error(t_token *first_inserted, t_token *current,
	t_token *current_next)
{
	if (!current)
		return (false);
	if (first_inserted)
	{
		current->next = current_next;
		ft_free_token_list(first_inserted);
	}
	return (false);
}

static bool	ft_insert_remaining_tokens(t_token *current, char **matches,
	t_token *current_next, t_token **last_inserted)
{
	t_token	*node;
	t_token	*first_inserted;
	int		i;

	if (!current || !matches || !last_inserted)
		return (false);
	first_inserted = NULL;
	i = 1;
	while (matches[i])
	{
		node = ft_create_token(matches[i], TOKEN_WORD);
		if (!node)
			return (ft_handle_insert_error(first_inserted, current,
				current_next));
		if (!first_inserted)
			first_inserted = node;
		(*last_inserted)->next = node;
		*last_inserted = node;
		i++;
	}
	return (true);
}

t_token	*ft_replace_current_token_with_matches(t_token *current, char **matches)
{
	t_token	*current_next;
	t_token	*last_inserted;

	if (!current || !matches)
		return (NULL);
	if (!matches[0])
		return (current);
	current_next = current->next;
	last_inserted = current;
	if (!ft_update_first_token_value(current, matches[0], matches))
		return (NULL);
	if (!ft_insert_remaining_tokens(current, matches, current_next,
		&last_inserted))
		return (NULL);
	last_inserted->next = current_next;
	return (last_inserted);
}

