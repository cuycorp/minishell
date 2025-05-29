/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenize_redirection.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 15:08:43 by jgossard          #+#    #+#             */
/*   Updated: 2025/05/29 16:23:05 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token_type	ft_parse_redirection_token_type(
	char *str, unsigned int *pos)
{
	if (str[*pos] == '<')
	{
		if (str[(*pos)++] && str[*pos] == '<')
		{
			(*pos)++;
			return (TOKEN_HEREDOC);
		}
		return (TOKEN_REDIRECT_IN);
	}
	else if (str[*pos] == '>')
	{
		if (str[(*pos)++] && str[*pos] == '>')
		{
			(*pos)++;
			return (TOKEN_APPEND_OUT);
		}
		return (TOKEN_REDIRECT_OUT);
	}
	return (TOKEN_UNKNOWN);
}

void	ft_tokenize_redirection(char *str, unsigned int *pos, t_shell *data)
{
	t_token_type	token_type;
	char			*token;
	unsigned int	start_index;
	int				length;

	if (!str || pos < 0)
		return ;
	start_index = *pos;
	token_type = ft_get_redirection_token_type(str, pos);
	length = *pos - start_index;
	token = ft_substr(str, start_index, length);
	if (!token)
		return (ft_close_program(data, EXIT_FAILURE));
	ft_add_token(&data->tokens_list, ft_create_token(token, token_type));
}
