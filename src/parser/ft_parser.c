/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 11:41:53 by mcamaren          #+#    #+#             */
/*   Updated: 2025/06/19 13:36:26 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_parser(t_token *token_list)
{
	t_token	*current;

	current = token_list;
	if (!ft_parse_shell(&current))
		return (false);
	return (true);
}
