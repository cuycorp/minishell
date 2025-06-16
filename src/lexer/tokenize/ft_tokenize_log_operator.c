/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenize_log_operator.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamaren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:13:43 by mcamaren          #+#    #+#             */
/*   Updated: 2025/06/03 15:13:46 by mcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_tokenize_log_operator(char *str, unsigned int *pos, t_shell *data)
{
	t_token	*new_token;
	char	*token;
	int		length;

	if (str[*pos] == '|' && str[(*pos) + 1] == '|')
		token = ft_strdup("||");
	else if (str[*pos] == '&' && str[(*pos) + 1] == '&')
		token = ft_strdup("&&");
	else
		return (ft_close_program(data, EXIT_FAILURE));
	length = 2;
	(*pos) += length;
	if (!token)
		return (ft_close_program(data, EXIT_FAILURE));
	new_token = ft_create_token(token, TOKEN_LOGICAL_OR);
	if (!new_token)
		return (free(token));
	ft_add_token(&data->tokens_list, new_token);
}
