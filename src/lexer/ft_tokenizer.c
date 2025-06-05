/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 15:55:53 by jgossard          #+#    #+#             */
/*   Updated: 2025/06/05 11:17:24 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_tokenizer(char *str, t_shell *data)
{
	unsigned int	i;

	i = 0;
	while (str[i])
	{
		while (ft_isspace(str[i]))
			i++;
		if (str[i] == '>' || str[i] == '<')
			ft_tokenize_redirection(str, &i, data);
		else if (str[i] == '&' || str[i] == '|')
			ft_tokenize_log_operator(str, &i, data);
		else if (str[i] == '(' || str[i] == ')')
			ft_tokenize_parenthesis(str, &i, data);
		else if (str[i] == '|' || str[i] == '$')
			ft_tokenize_single(str, &i, data);
		else if (str[i] == '"' || str[i] == '\'' || ft_is_unquoted_char(str[i]))
			ft_tokenize_mixed_word(str, &i, data);
		else if (str[i] == '\0')
			break ;
		else
		{
			ft_tokenize_unknown(str, &i, data);
			break ;
		}
	}
	ft_print_tokens_list(data);
}
