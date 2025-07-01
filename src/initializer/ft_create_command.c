/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_command.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 10:44:37 by jgossard          #+#    #+#             */
/*   Updated: 2025/07/01 19:33:47 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*ft_create_command(int argc)
{
	t_command	*new_command;

	if (argc <= 0)
		return (NULL);
	new_command = ft_alloc_struct(sizeof(t_command));
	if (!new_command)
		return (NULL);
	new_command->args = malloc(sizeof(char *) * (argc + 1));
	if (!new_command->args)
		return (ft_free_command(new_command), NULL);
	new_command->args[argc] = NULL;
	new_command->name = NULL;
	new_command->redirection = NULL;
	return (new_command);
}
