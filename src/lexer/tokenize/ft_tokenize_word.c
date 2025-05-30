/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenize_word.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 14:02:29 by jgossard          #+#    #+#             */
/*   Updated: 2025/05/30 17:04:03 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_tokenize_word(char *str, unsigned int *pos, t_shell *data)
{
	t_token			*new_token;
	char			*token;
	unsigned int	start_index;
	int				length;

	if (!str)
		return ;
	start_index = *pos;
	while (str[*pos]
		&& (ft_isalnum(str[*pos]) || ft_is_special_char(str[*pos])))
		(*pos)++;
	length = *pos - start_index;
	token = ft_substr(str, start_index, length);
	if (!token)
		return (ft_close_program(data, EXIT_FAILURE));
	new_token = ft_create_token(token, TOKEN_WORD);
	if (!new_token)
		return (free(token), ft_close_program(data, EXIT_FAILURE));
	ft_add_token(&data->tokens_list, new_token);
}
