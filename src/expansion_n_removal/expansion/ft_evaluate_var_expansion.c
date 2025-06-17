/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_var_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 18:45:22 by mcamaren          #+#    #+#             */
/*   Updated: 2025/07/09 11:23:58 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool ft_is_expandable(t_token_type type)
{
	if (type == TOKEN_DOUBLE_QUOTED_WORD || type == TOKEN_WORD || type == TOKEN_SINGLE_QUOTED_WORD ||  type == TOKEN_EXPANSION)
		return (true);
	return (false);
}

bool	ft_evaluate_var_expansion(t_token **token_list, t_shell *data)
{
	t_token	*current;
	char	*tmp;

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
				current->value  = ft_fill_expanded_variables(tmp, data);
				free(tmp);
				if (!current->value)
					return (false);
			}
			current = current->next;
		}
	}
	return (true);
}


/*
	TODO:
	=> since the function ft_append_char does not end the program,
		* a truthy return value should be 1
		* and a falsy return value should be 0,
	here this is the opposite so it is not correct
	- convert function from int -> Bool type to reduce interpretatiion of return value of 1 and 0
	- OR create variable to store the value and call them instead of doing return (1) / return (0);
*/

