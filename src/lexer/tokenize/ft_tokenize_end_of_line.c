/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenize_end_of_line.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:54:04 by jgossard          #+#    #+#             */
/*   Updated: 2025/08/01 15:00:21 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_tokenize_end_of_line(unsigned int *pos, t_shell *data)
{
	t_token	*new_token;
	char	*token;
	int		length;

	if (!pos || !data)
		return ;
	length = 1;
	(*pos) += length;
	token = ft_strdup("\0");
	if (!token)
		return (ft_close_program(data, EXIT_FAILURE));
	new_token = ft_create_token(token, TOKEN_END_OF_LINE);
	if (!new_token)
		return (free(token));
	ft_add_token(&data->tokens_list, new_token);
	free(token);
}
