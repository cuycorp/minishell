/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenize_expansion.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 10:34:17 by jgossard          #+#    #+#             */
/*   Updated: 2025/08/01 15:04:09 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_expand_identifier(char *str, unsigned int *pos)
{
	if (str[*pos] == '?')
		(*pos)++;
	else
	{
		while (str[*pos])
		{
			if (ft_isalnum(str[*pos]) || str[*pos] == '_')
				(*pos)++;
			else
				break ;
		}
	}
}

static void	ft_expand_trailing(char *str, unsigned int *pos)
{
	while (str[*pos])
	{
		if (ft_is_valid_expansion(str[*pos]))
			(*pos)++;
		else if (ft_isalnum(str[*pos]) || str[*pos] == '_')
			(*pos)++;
		else if (str[*pos] == '?')
			(*pos)++;
		else
			break ;
	}
}

void	ft_tokenize_expansion(char *str, unsigned int *pos, t_shell *data)
{
	unsigned int	start_index;
	t_token_type	type;

	ft_printf(STDERR_FILENO, "ft_tokenize_expansion\n");
	if (!str || !pos || !data)
		return ;
	type = TOKEN_EXPANSION;
	start_index = *pos;
	(*pos)++;
	ft_expand_identifier(str, pos);
	ft_expand_trailing(str, pos);
	ft_add_token_from_range(data, start_index, *pos, type);
}
