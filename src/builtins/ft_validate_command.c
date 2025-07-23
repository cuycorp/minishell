/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_validate_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamaren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 16:52:45 by mcamaren          #+#    #+#             */
/*   Updated: 2025/07/23 16:52:47 by mcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_validate_command(t_command *command, char *commmand_name)
{
	if (ft_strncmp(commmand_name, command->args[0],
			ft_strlen(command->args[0])))
		return (false);
	if (ft_strncmp(commmand_name, command->args[0], ft_strlen(commmand_name)))
		return (false);
	if (ft_strncmp(commmand_name, command->name, ft_strlen(command->name)))
		return (false);
	if (ft_strncmp(commmand_name, command->name, ft_strlen(commmand_name)))
		return (false);
	return (true);
}
