/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_token_from_range.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 17:00:55 by jgossard          #+#    #+#             */
/*   Updated: 2025/06/27 11:31:20 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_add_token_from_range(t_shell *data, int start, int end,
		t_token_type type)
{
	char	*token;
	t_token	*new_token;

	if (!data || !data->input)
	{
		perror("Error: failed in ft_add_token_from_range");
		return (ft_close_program(data, EXIT_FAILURE));
	}
	token = ft_substr(data->input, start, end - start);
	if (!token)
		ft_close_program(data, EXIT_FAILURE);
	new_token = ft_create_token(token, type);
	if (!new_token)
	{
		free(token);
		ft_close_program(data, EXIT_FAILURE);
	}
	ft_add_token(&data->tokens_list, new_token);
	free(token);
}
