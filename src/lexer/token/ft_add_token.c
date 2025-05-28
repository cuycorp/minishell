/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 22:19:39 by jg                #+#    #+#             */
/*   Updated: 2025/05/28 12:10:24 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Adds a new token to the end of the token list.
 *
 * If the token list is empty, the new token becomes the head of the list.
 * Otherwise, the function appends the new token at the end.
 *
 * @param tokens_list Double pointer pointing to the start of the token list.
 * @param new_token The token to add to the list.
 */
void	ft_add_token(t_token **tokens_list, t_token *new_token)
{
	t_token	*tmp;

	if (!tokens_list || !new_token)
		return (perror("Error: ft_add_token failed."));
	if (!(*tokens_list))
		*tokens_list = new_token;
	else
	{
		tmp = *tokens_list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_token;
	}
}
