/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenize_expansion.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 10:34:17 by jgossard          #+#    #+#             */
/*   Updated: 2025/07/01 20:46:18 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_tokenize_expansion(char *str, unsigned int *pos, t_shell *data)
{
	unsigned int	start_index;
	t_token_type	type;

	if (!str)
		return ;
	type = TOKEN_EXPANSION;
	start_index = *pos;
	(*pos)++;
	if (str[*pos] == '?')
		(*pos)++;
	else
	{
		while (str[*pos] && (ft_isalnum(str[*pos]) || str[*pos] == '_'))
			(*pos)++;
	}
	ft_add_token_from_range(data, start_index, *pos, type);
}
