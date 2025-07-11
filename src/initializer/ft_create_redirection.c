/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_redirection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 10:27:41 by jgossard          #+#    #+#             */
/*   Updated: 2025/07/21 16:38:39 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redirection	*ft_create_redirection(t_redirection_type type, char *target)
{
	t_redirection	*redirection;

	if (type == UNKNOWN || !target)
		return (NULL);
	redirection = ft_alloc_struct(sizeof(t_redirection));
	if (!redirection)
		return (NULL);
	redirection->type = type;
	if (target)
		redirection->target = ft_strdup(target);
	redirection->heredoc_fd = -1;
	return (redirection);
}
