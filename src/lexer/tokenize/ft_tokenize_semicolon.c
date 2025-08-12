/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenize_semicolon.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamaren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 17:22:37 by mcamaren          #+#    #+#             */
/*   Updated: 2025/08/12 17:22:40 by mcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_tokenize_semicolon(char *str, unsigned int *pos, t_shell *data)
{
	t_token	*new_token;
	char	*token;
	int		length;

	if (!data || !str || !pos)
		return ;
	length = 1;
	token = ft_substr(str, *pos, length);
	if (!token)
		return (ft_close_program(data, EXIT_FAILURE));
	new_token = ft_create_token(token, TOKEN_UNKNOWN);
	if (!new_token)
		return (free(token));
	ft_add_token(&data->tokens_list, new_token);
	free(token);
	(*pos)++;
}

