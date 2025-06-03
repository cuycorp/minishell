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

void	ft_tokenize_log_operator(unsigned int *pos, t_shell *data,
		char operator)
{
	t_token	*new_token;
	char	*token;
	int		length;

	length = 2;
	(*pos) += length;
	if (operator== '|')
		token = ft_strdup("||");
	else
		token = ft_strdup("&&");
	if (!token)
		return (ft_close_program(data, EXIT_FAILURE));
	new_token = ft_create_token(token, TOKEN_LOGICAL_OR);
	if (!new_token)
		return (free(token));
	ft_add_token(&data->tokens_list, new_token);
}
