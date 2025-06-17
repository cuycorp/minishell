/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_valid_delimiter_token.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamaren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 12:22:11 by mcamaren          #+#    #+#             */
/*   Updated: 2025/07/22 12:22:15 by mcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_is_valid_delimiter_token(t_token_type type)
{
	if (type == TOKEN_DOUBLE_QUOTED_WORD || type == TOKEN_SINGLE_QUOTED_WORD
		|| type == TOKEN_WORD || type == TOKEN_EXPANSION)
		return (true);
	return (false);
}
