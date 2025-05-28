/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tokens_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jg <jg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 22:57:22 by jg                #+#    #+#             */
/*   Updated: 2025/05/27 23:07:42 by jg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_tokens_list(t_token **tokens_list)
{
	t_token	*current;
	t_token	*next;

	if (!tokens_list)
		return ;
	current = *tokens_list;
	while (current)
	{
		next = current->next;
		free(current->value);
		free(current);
		current = next;
	}
	*tokens_list = NULL;
}
