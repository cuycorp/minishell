/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenize_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamaren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:56:48 by mcamaren          #+#    #+#             */
/*   Updated: 2025/05/29 16:56:51 by mcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_tokenize_pipe(char *str, unsigned int *pos, t_shell *data)
{
	t_token	*new_token;
	char	*token;
	int		length;

	length = 2;
	(*pos) += length;
	token = ft_strdup("|");
	if (!token)
		return (ft_close_program(data, EXIT_FAILURE));
	new_token = ft_create_token(token, TOKEN_PIPE);
	if (!new_token)
		return (free(token));
	ft_add_token(&data->tokens_list, new_token);
}
