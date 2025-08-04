/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenize_unknown.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 17:03:00 by mcamaren          #+#    #+#             */
/*   Updated: 2025/08/01 15:07:52 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_tokenize_unknown(char *str, unsigned int *pos, t_shell *data)
{
	t_token	*new_token;
	char	*token;
	int		length;

	if (!str || !data || !pos)
		return ;
	length = 1;
	(*pos) += length;
	token = ft_strdup(str);
	if (!token)
		return (ft_close_program(data, EXIT_FAILURE));
	new_token = ft_create_token(token, TOKEN_UNKNOWN);
	if (!new_token)
		return (free(token));
	ft_add_token(&data->tokens_list, new_token);
	free(token);
}
