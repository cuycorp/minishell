/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_wildcards_in_token_list.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 18:04:03 by jgossard          #+#    #+#             */
/*   Updated: 2025/08/13 15:31:57 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	ft_handle_redirection_wildcard(t_token **current, t_shell *data)
{
	if (!current || !*current || !(*current)->next || !data)
		return (false);
	if (!ft_expand_wildcard_for_redirection((*current)->next, data))
		return (false);
	*current = (*current)->next->next;
	return (true);
}

static bool	ft_handle_regular_wildcard(t_token **current, t_shell *data)
{
	t_token	*last;
	char	**matches_result;

	if (!current || !*current || !data)
		return (false);
	matches_result = ft_resolve_wildcard_pattern((*current)->value, data);
	if (!matches_result)
		return (false);
	last = ft_replace_current_token_with_matches(*current, matches_result);
	ft_free_char_tab(matches_result);
	if (!last)
		return (false);
	*current = last->next;
	return (true);
}

static bool	ft_is_expansion_wildcard(t_token *current)
{
	if (ft_is_redirection_type(current->type) && current->next
		&& current->next->type == TOKEN_WORD
		&& ft_has_wildcard(current->next->value))
		return (true);
	return (false);
}

static bool	ft_is_regular_wildcard(t_token *current)
{
	if (current->type == TOKEN_WORD && current->value
		&& ft_has_wildcard(current->value))
		return (true);
	return (false);
}

bool	ft_expand_wildcards_in_token_list(t_token **tokens, t_shell *data)
{
	t_token	*current;

	if (!tokens || !data)
		return (false);
	current = *tokens;
	while (current)
	{
		if (ft_is_expansion_wildcard(current))
		{
			if (!ft_handle_redirection_wildcard(&current, data))
			{
				current = current->next->next;
				continue ;
			}
			continue ;
		}
		if (ft_is_regular_wildcard(current))
		{
			if (!ft_handle_regular_wildcard(&current, data))
				return (false);
			continue ;
		}
		current = current->next;
	}
	return (true);
}
