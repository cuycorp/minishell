/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenize_single.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamaren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:27:50 by mcamaren          #+#    #+#             */
/*   Updated: 2025/06/03 15:28:26 by mcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_tokenize_pipe(unsigned int *pos, t_shell *data)
{
	t_token	*new_token;
	char	*token;
	int		length;

	length = 1;
	(*pos) += length;
	token = ft_strdup("|");
	if (!token)
		return (ft_close_program(data, EXIT_FAILURE));
	new_token = ft_create_token(token, TOKEN_PIPE);
	if (!new_token)
		return (free(token));
	ft_add_token(&data->tokens_list, new_token);
}

void	ft_tokenize_expansion(char *str, unsigned int *pos, t_shell *data)
{
	unsigned int	start_index;

	if (!str)
		return ;
	start_index = *pos;
	(*pos)++;
	if (str[*pos] == '?')
		(*pos)++;
	else
	{
		while (str[*pos] && (ft_isalnum(str[*pos]) || str[*pos] == '_'))
			(*pos)++;
	}
	ft_add_token_from_range(data, start_index, *pos, TOKEN_EXPANSION);
}

void	ft_tokenize_double_quote(char *str, unsigned int *pos, t_shell *data)
{
	int	start_index;

	if (!str)
		return ;
	start_index = *pos;
	ft_handle_double_quoted_word_token(str, pos);
	while (ft_is_unquoted_char(str[*pos]))
		(*pos)++;
	ft_add_token_from_range(data, start_index, *pos, TOKEN_DOUBLE_QUOTED_WORD);
}

void	ft_tokenize_single_quote(unsigned int *pos, t_shell *data)
{
	t_token	*new_token;
	char	*token;
	int		length;

	length = 1;
	(*pos) += length;
	token = ft_strdup("'");
	if (!token)
		return (ft_close_program(data, EXIT_FAILURE));
	new_token = ft_create_token(token, TOKEN_PIPE);
	if (!new_token)
		return (free(token));
	ft_add_token(&data->tokens_list, new_token);
}

ft_tokenize_single(char *str, unsigned int *pos, t_shell *data)
{
}
