/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenize_parenthesis.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 17:40:44 by jgossard          #+#    #+#             */
/*   Updated: 2025/05/30 18:10:09 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_tokenize_parenthesis(char *str, unsigned int *pos, t_shell *data)
{
	t_token_type	token_type;
	char			*token;
	unsigned int	start_index;
	int				length;

	if (!str)
		return ;
	start_index = *pos;
	if (str[*pos] == '(')
		token_type = TOKEN_PARENTHESIS_LEFT;
	else if (str[*pos] == ')')
		token_type = TOKEN_PARENTHESIS_RIGHT;
	(*pos)++;
	length = *pos - start_index;
	token = ft_substr(str, start_index, length);
	if (!token)
		return (ft_close_program(data, EXIT_FAILURE));
	ft_add_token(&data->tokens_list, ft_create_token(token, token_type));
}
