/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_word.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 14:08:31 by jgossard          #+#    #+#             */
/*   Updated: 2025/06/19 13:45:47 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_parse_word(t_token **token_list)
{
	if (!token_list || !(*token_list))
		return (false);
	if (ft_is_word_like_type((*token_list)->type))
	{
		ft_advance_token(token_list);
		return (true);
	}
	return (ft_parse_error("expected a word"));
}
