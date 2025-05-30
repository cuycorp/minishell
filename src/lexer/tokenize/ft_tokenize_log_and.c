/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenize_log_and.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamaren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:55:53 by mcamaren          #+#    #+#             */
/*   Updated: 2025/05/29 16:55:56 by mcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_tokenize_log_and(char *str, unsigned int *pos, t_shell *data)
{
	t_token	*new_token;
	char	*token;
	int		length;

	length = 2;
	(*pos) += length;
	token = ft_strdup("&&");
	if (!token)
		return (ft_close_program(data, EXIT_FAILURE));
	new_token = ft_create_token(token, TOKEN_LOGICAL_AND);
	if (!new_token)
		return (free(token));
	ft_add_token(&data->tokens_list, new_token);
}

/*
update index
set length of token string
set string of token
validate correct allocation
create token
validate token
add token to the list
*/
