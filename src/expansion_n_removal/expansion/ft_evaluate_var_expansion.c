/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_evaluate_var_expansion.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 18:45:22 by mcamaren          #+#    #+#             */
/*   Updated: 2025/08/01 15:09:37 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	ft_is_expandable(t_token_type type)
{
	if (type == TOKEN_DOUBLE_QUOTED_WORD || type == TOKEN_WORD
		|| type == TOKEN_SINGLE_QUOTED_WORD || type == TOKEN_EXPANSION)
		return (true);
	return (false);
}

bool	ft_evaluate_var_expansion(t_token **token_list, t_shell *data)
{
	t_token	*current;
	char	*tmp;

	if (!token_list || !*token_list || !data)
		return (false);
	current = *token_list;
	while (current)
	{
		if (current->type == TOKEN_HEREDOC && current->next
			&& ft_is_valid_delimiter_token(current->next->type))
			current = current->next->next;
		else
		{
			if (ft_is_expandable(current->type))
			{
				tmp = current->value;
				current->value = ft_fill_expanded_variables(tmp, data);
				free(tmp);
				if (!current->value)
					return (false);
			}
			current = current->next;
		}
	}
	return (true);
}
