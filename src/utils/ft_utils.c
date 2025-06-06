/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamaren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 16:09:43 by mcamaren          #+#    #+#             */
/*   Updated: 2025/06/06 16:09:45 by mcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_is_redirection_type(t_token_type type)
{
	return (type == TOKEN_REDIRECT_IN || type == TOKEN_REDIRECT_OUT
		|| type == TOKEN_HEREDOC || type == TOKEN_APPEND_OUT);
}

bool	ft_is_argument_type(t_token_type type)
{
	return (type == TOKEN_WORD || type == TOKEN_DOUBLE_QUOTED_WORD
		|| type == TOKEN_SINGLE_QUOTED_WORD);
}
