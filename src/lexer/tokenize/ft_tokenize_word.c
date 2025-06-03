/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenize_word.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 14:02:29 by jgossard          #+#    #+#             */
/*   Updated: 2025/06/03 09:48:44 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_tokenize_word(char *str, unsigned int *pos, t_shell *data)
{
	unsigned int	start_index;

	if (!str)
		return ;
	start_index = *pos;
	while (str[*pos] && (ft_is_unquoted_char(str[*pos])))
		(*pos)++;
	ft_add_token_from_range(data, start_index, *pos, TOKEN_WORD);
}
