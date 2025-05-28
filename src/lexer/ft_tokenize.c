/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 15:55:53 by jgossard          #+#    #+#             */
/*   Updated: 2025/05/28 16:03:54 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void ft_get_next_token(char *str, unsigned int *pos, t_shell *data)
{
	if (!str || pos < 0)
		return ;
	if (str[*pos] && ft_isalnum(str[*pos]))
		ft_scan_alnum_token(str, pos, data);
}

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
			ft_get_next_token(str, &i, data);
		else
		{
			ft_printf(1, "character unknown\n");
			break;
		}
	}
	ft_print_tokens_list(data);
}
