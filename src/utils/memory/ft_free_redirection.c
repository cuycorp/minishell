/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 10:36:31 by jgossard          #+#    #+#             */
/*   Updated: 2025/06/25 23:43:16 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_redirection(t_redirection **redirection)
{
	t_redirection	*current;
	t_redirection	*next;

	if (!redirection || !(*redirection))
		return ;
	current = *redirection;
	while (current)
	{
		next = current->next;
		if (current->target)
		{
			free(current->target);
			current->target = NULL;
		}
		free(current);
		current = next;
	}
	*redirection = NULL;
}
