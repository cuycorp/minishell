/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_arguments.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 14:09:03 by jgossard          #+#    #+#             */
/*   Updated: 2025/06/19 15:53:37 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_parse_arguments(t_token **token_list)
{
	if (!token_list || !(*token_list))
		return (false);
	if (ft_is_word_like_type((*token_list)->type))
	{
		ft_advance_token(token_list);
		return (true);
	}
	if ((*token_list)->type == TOKEN_EXPANSION)
		return (ft_parse_env_variable(token_list));
	return (ft_parse_error("expected argument"));
}
