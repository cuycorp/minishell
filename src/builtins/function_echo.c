/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamaren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 18:21:50 by mcamaren          #+#    #+#             */
/*   Updated: 2025/06/11 18:21:54 by mcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool ft_validate_option(char *option, int *i)
{
	bool nl_flag;

	nl_flag = true;
	if (!option)
		return (nl_flag);
	if (ft_strncmp("-n", option, ft_strlen(option)) == 0)
	{
		nl_flag = false;
		(*i)++;
	}
	return (nl_flag);
}




int	function_echo(t_command *command)
{
	bool	nl_flag;
	int		i;

	i = 0;
	if (!command->args[0])
		return (1);
	if (ft_validate_command(command, "echo") == false)
		return (1);
	i = 1;
	nl_flag = ft_validate_option(command->args[i], &i);
	while (command->args[i])
	{
		ft_printf(STDOUT_FILENO, "%s", command->args[i]);
		if (command->args[i + 1])
			ft_printf(STDOUT_FILENO, " ");
		i++;
	}
	if (nl_flag)
		ft_printf(STDOUT_FILENO, "\n");
	return (0);
}

/*
check command
	+ command name
	+ command first argument
check option
	if correct set flag to put new line and jump to next
loop over arguments printing
*/
