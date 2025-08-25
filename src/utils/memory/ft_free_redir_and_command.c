/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_redirection_and_command.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 14:51:08 by jgossard          #+#    #+#             */
/*   Updated: 2025/08/22 14:53:23 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_redir_and_command(t_redirection **redirections,
		t_command *command)
{
	if (redirections)
		ft_free_redirection(redirections);
	if (command)
		ft_free_command(command);
}
