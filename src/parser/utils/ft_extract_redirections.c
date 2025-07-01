/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extract_redirections.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 14:41:45 by jgossard          #+#    #+#             */
/*   Updated: 2025/07/01 16:32:34 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_add_last_redirection(t_redirection **list, t_redirection *new)
{
	t_redirection	*current;

	if (!list || !new)
		return ;
	if (!(*list))
	{
		*list = new;
	}
	else
	{
		current = *list;
		while (current->next)
			current = current->next;
		current->next = new;
	}
}

bool	ft_extract_redirections(t_redirection **redirection_list,
		t_token **tokens, bool *has_redirection)
{
	t_redirection	*redirection;

	while ((*tokens) && ft_is_redirection_type((*tokens)->type))
	{
		redirection = ft_parse_redirection(tokens);
		if (!redirection)
		{
			ft_free_redirection(redirection_list);
			return (false);
		}
		ft_add_last_redirection(redirection_list, redirection);
		*has_redirection = true;
	}
	return (true);
}
