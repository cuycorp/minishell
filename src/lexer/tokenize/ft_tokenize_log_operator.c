/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenize_log_operator.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:13:43 by mcamaren          #+#    #+#             */
/*   Updated: 2025/08/01 15:03:19 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token_type	ft_get_logical_operator_token_type(
	char *str, unsigned int *pos)
{
	if (str[*pos] == PIPE)
	{
		if (str[(*pos)++] && str[*pos] == PIPE)
		{
			(*pos)++;
			return (TOKEN_LOGICAL_OR);
		}
		return (TOKEN_PIPE);
	}
	else if (str[*pos] == AMPERSAND_OPERATOR)
	{
		if (str[(*pos)++] && str[*pos] == AMPERSAND_OPERATOR)
		{
			(*pos)++;
			return (TOKEN_LOGICAL_AND);
		}
		return (TOKEN_UNKNOWN);
	}
	return (TOKEN_UNKNOWN);
}

void	ft_tokenize_log_operator(char *str, unsigned int *pos, t_shell *data)
{
	t_token_type	token_type;
	char			*token;
	unsigned int	start_index;
	int				length;

	if (!str || !pos || !data)
		return ;
	start_index = *pos;
	token_type = ft_get_logical_operator_token_type(str, pos);
	length = *pos - start_index;
	token = ft_substr(str, start_index, length);
	if (!token)
		return (ft_close_program(data, EXIT_FAILURE));
	ft_add_token(&data->tokens_list, ft_create_token(token, token_type));
	free(token);
}
