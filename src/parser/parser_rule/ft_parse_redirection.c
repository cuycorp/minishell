/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_redirection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 14:07:55 by jgossard          #+#    #+#             */
/*   Updated: 2025/06/19 13:46:08 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_parse_redirection(t_token **token_list)
{
	if (!token_list || !(*token_list))
		return (false);
	if (!ft_is_redirection_type((*token_list)->type))
		return (ft_parse_error("expected redirection operator"));
	ft_advance_token(token_list);
	if (!(*token_list) || !ft_is_word_like_type((*token_list)->type))
		return (ft_parse_error("expected filename after redirection"));
	return (ft_parse_word(token_list));
}
