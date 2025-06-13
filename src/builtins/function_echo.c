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

int	function_echo(t_command command)
{
	bool	nl_flag;
	int		i;

	i = 0;
	nl_flag = false;
	if (ft_strncmp("-n", command.args[i], ft_strlen("-n")) == 0)
	{
		nl_flag = true;
		i++;
	}
	while (command.args[i])
	{
		ft_printf(STDOUT_FILENO, "%s", command.args[i]);
		if (command.args[i + 1])
			ft_printf(STDOUT_FILENO, " ");
		i++;
	}
	if (nl_flag)
		ft_printf(STDOUT_FILENO, "\n");
	return (0);
}
