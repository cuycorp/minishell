/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenize_single_quote.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamaren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 11:35:47 by mcamaren          #+#    #+#             */
/*   Updated: 2025/06/03 11:36:09 by mcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


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

