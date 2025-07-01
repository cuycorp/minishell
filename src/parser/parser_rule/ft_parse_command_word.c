/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_command_word.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 15:00:34 by jgossard          #+#    #+#             */
/*   Updated: 2025/07/01 19:29:15 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_parse_command_word(t_token **tokens)
{
	char	*command_word;

	if (!tokens || !(*tokens))
		return (NULL);
	if (ft_is_word_like_type((*tokens)->type))
	{
		command_word = ft_strdup((*tokens)->value);
		if (!command_word)
			return (NULL);
		ft_advance_token(tokens);
		return (command_word);
	}
	if ((*tokens)->type == TOKEN_EXPANSION)
		return (ft_parse_env_variable(tokens));
	return (NULL);
}
