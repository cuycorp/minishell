/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_verify_balanced_quotes.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamaren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 17:08:09 by mcamaren          #+#    #+#             */
/*   Updated: 2025/07/23 17:08:12 by mcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_are_quotes_balanced(char *str)
{
	t_quotes	quote;

	quote = NONE;
	while (*str)
	{
		if (quote == NONE)
		{
			if (*str == '\'')
				quote = SINGLE;
			else if (*str == '"')
				quote = DOUBLE;
		}
		else if (quote == SINGLE)
		{
			if (*str == '\'')
				quote = NONE;
		}
		else if (quote == DOUBLE)
		{
			if (*str == '"')
				quote = NONE;
		}
		str++;
	}
	return (quote == NONE);
}
