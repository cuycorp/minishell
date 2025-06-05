/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_quoted_string.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 14:10:06 by jgossard          #+#    #+#             */
/*   Updated: 2025/06/19 13:43:41 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_parse_quoted_string(t_token **token_list)
{
	if (!token_list || !(*token_list))
		return (false);
	if (ft_match_token(token_list, TOKEN_DOUBLE_QUOTED_WORD)
		|| ft_match_token(token_list, TOKEN_SINGLE_QUOTED_WORD))
		return (true);
	return (ft_parse_error("expected a quoted string"));
}
