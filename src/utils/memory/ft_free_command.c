/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:05:07 by mcamaren          #+#    #+#             */
/*   Updated: 2025/07/01 14:09:39 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_command(t_command *command)
{
	if (!command)
		return ;
	if (command->args)
	{
		ft_free_char_tab(command->args);
		command->args = NULL;
	}
	if (command->name)
	{
		free(command->name);
		command->name = NULL;
	}
	if (command->redirection)
	{
		ft_free_redirection(&command->redirection);
		command->redirection = NULL;
	}
	free(command);
}
