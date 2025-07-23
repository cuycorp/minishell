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

static bool	ft_validate_option(char *option, int *i)
{
	bool	nl_flag;
	int		j;

	j = 0;
	nl_flag = true;
	if (!option)
		return (nl_flag);
	if (option[j] != '-')
		return (nl_flag);
	j++;
	while (option[j])
	{
		if (option[j] == 'n')
			nl_flag = false;
		else
		{
			nl_flag = true;
			break ;
		}
		j++;
	}
	if (nl_flag == false)
		(*i)++;
	return (nl_flag);
}

static bool	ft_is_valid_skip(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] != '-')
		return (false);
	i++;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

static void	ft_skip_option(char **args, int *i)
{
	while (args[*i])
	{
		if (ft_is_valid_skip(args[*i]))
			(*i)++;
		else
			break ;
	}
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
	ft_skip_option(command->args, &i);
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
