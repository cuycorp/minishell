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

void	ft_tokenize_expansion(char *str, unsigned int *pos, t_shell *data)
{
	unsigned int	start_index;
	t_token_type	type;

	if (!str || !pos || !data)
		return ;
	type = TOKEN_EXPANSION;
	start_index = *pos;
	(*pos)++;
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
	while (str[*pos])
	{
		if (ft_is_valid_expansion(str[*pos]))
			(*pos)++;
		else if (ft_isalnum(str[*pos]) || str[*pos] == '_')
			(*pos)++;
		else if(str[*pos] == '?')
			(*pos)++;
		else
			break ;
	}
	ft_add_token_from_range(data, start_index, *pos, type);
}

// $USER_123-e
 /*
 -> token_word :
 1. replace existing env variables
 2. $"" or $'' are left as they are
	$USER$"aa" ->  mcamaren$"aa" -->  mcamaren$aa
 3. non existent variables return empty
 */
