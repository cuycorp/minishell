/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_command_line.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 11:29:54 by jgossard          #+#    #+#             */
/*   Updated: 2025/06/19 13:41:07 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_parse_command_line(t_token **token_list)
{
	if (!token_list || !(*token_list))
		return (false);
	return (ft_parse_and_or_list(token_list));
}
