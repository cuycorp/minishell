/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:48:44 by jgossard          #+#    #+#             */
/*   Updated: 2025/06/04 14:22:59 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_check_quotes(char *str, unsigned int *pos, t_shell *data)
{
	bool	is_double_quotes_opened;
	bool	is_single_quote_opened;

	is_double_quotes_opened = false;
	while (str[*pos])
	{
		if (str[*pos] == '"')
			is_double_quotes_opened = !is_double_quotes_opened;
		else if (str[*pos] == '\'')
			is_single_quote_opened = !is_single_quote_opened;
		(*pos)++;
	}
	if (!is_double_quotes_opened)
	{
		perror("Error: double-quotes not closed");
		ft_close_program(data, EXIT_FAILURE);
	}
	else if (!is_single_quote_opened)
	{
		perror("Error: single-quote not closed");
		ft_close_program(data, EXIT_FAILURE);
	}
	return (true);
}
