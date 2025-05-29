/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 15:55:53 by jgossard          #+#    #+#             */
/*   Updated: 2025/05/29 16:23:05 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_tokenize(char *str, t_shell *data)
{
	(void)data;
	unsigned int	i;

	i = 0;
	while (str[i])
	{
		while (ft_isspace(str[i]))
			i++;
		if (ft_isalnum(str[i]))
			ft_scan_alnum_token(str, &i, data);
		else if (str[i] == '>' || str[i] == '<')
			ft_tokenize_redirection(str, &i, data);
		else
		{
			ft_printf(1, "character unknown\n");
			break;
		}
	}
	ft_print_tokens_list(data);
}
