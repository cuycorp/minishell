/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamaren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:50:07 by mcamaren          #+#    #+#             */
/*   Updated: 2025/07/09 18:50:15 by mcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	ft_check_first_arg(t_command *command)
{
	if (!command->args[0])
		return (false);
	if (ft_strncmp(command->args[0], "unset", ft_strlen(command->args[0])) == 0)
		return (true);
	return (false);
}

int	function_unset(t_command *command, t_shell *data)
{
	int	len_arg;

	len_arg = ft_len_table(command->args);
	if (!command || !data || len_arg == 0)
		return (EXIT_FAILURE);
	if (ft_validate_command(command, "unset") == false)
		return (EXIT_FAILURE);
	if (ft_strncmp(command->name, "unset", ft_strlen(command->name)))
		return (EXIT_FAILURE);
	if (ft_check_first_arg(command))
	{
		if (len_arg != 1)
		{
			if (!ft_unset_var(command, data))
				return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}
