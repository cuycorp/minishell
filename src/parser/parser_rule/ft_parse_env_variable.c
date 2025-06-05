/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_env_variable.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 14:20:18 by jgossard          #+#    #+#             */
/*   Updated: 2025/06/19 13:46:24 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_parse_env_variable(t_token **token_list)
{
	if (!token_list || !(*token_list))
		return (false);
	if (ft_match_token(token_list, TOKEN_EXPANSION))
		return (true);
	return (ft_parse_error("expected environment variable"));
}
