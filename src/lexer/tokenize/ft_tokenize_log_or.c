/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenize_log_or.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:56:14 by mcamaren          #+#    #+#             */
/*   Updated: 2025/05/30 18:12:31 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_tokenize_log_or(unsigned int *pos, t_shell *data)
{
	t_token	*new_token;
	char	*token;
	int		length;

	length = 2;
	(*pos) += length;
	token = ft_strdup("||");
	if (!token)
		return (ft_close_program(data, EXIT_FAILURE));
	new_token = ft_create_token(token, TOKEN_LOGICAL_OR);
	if (!new_token)
		return (free(token));
	ft_add_token(&data->tokens_list, new_token);
}

