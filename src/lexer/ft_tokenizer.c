/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 15:55:53 by jgossard          #+#    #+#             */
/*   Updated: 2025/06/03 10:42:52 by jgossard         ###   ########.fr       */
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
		else if (str[i] == '&' && str[i + 1] == '&')
			ft_tokenize_log_and(&i, data);
		else if (str[i] == '|' && str[i + 1] == '|')
			ft_tokenize_log_or(&i, data);
		else if (str[i] == '|')
			ft_tokenize_pipe(&i, data);
		else if (str[i] == '\0')
			ft_tokenize_EOL(&i, data);
		else if (str[i] == '(' || str[i] == ')')
			ft_tokenize_parenthesis(str, &i, data);
		else if (str[i] == '$')
			ft_tokenize_expansion(str, &i, data);
		else if (str[i] == '"')
			ft_tokenize_double_quote(str, &i, data);
		else if (ft_is_unquoted_char(str[i]))
			ft_tokenize_word(str, &i, data);
		else
		{
			ft_tokenize_unknown(str, &i, data);
			break ; // TODO: change to return instead? in order to stop computing whenever we have an issue?
		}
	}
	ft_print_tokens_list(data);
}
