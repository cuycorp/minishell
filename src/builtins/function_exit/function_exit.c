/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 19:42:31 by mcamaren          #+#    #+#             */
/*   Updated: 2025/08/11 20:47:26 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_is_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	exit_extra_args(t_command *command, t_shell *data)
{
	if (!command || !command->args || !command->args[1])
		return (1);
	if (!ft_is_number(command->args[1]))
	{
		ft_printf(STDERR_FILENO, "bash: exit: %s: numeric argument required\n",
			command->args[1]);
		return (ft_close_program(data, 2), 2);
	}
	else
	{
		if (data->exit_code == 0)
			data->exit_code = 1;
		return (ft_printf(STDERR_FILENO, "bash: exit: too many arguments\n"),
		data->exit_code);
	}
}

static int	exit_exact_args(t_command *command, t_shell *data, int len)
{
	long long	exit_code;
	bool		is_valid_num;

	is_valid_num = true;
	exit_code = ft_atoll(command->args[1], &is_valid_num) % 256;
	if (len == 1)
		return (ft_close_program(data, 0), 0);
	else
	{
		if (ft_is_number(command->args[1]) && is_valid_num)
			return (ft_close_program(data, exit_code), exit_code);
		else
		{
			ft_printf(STDERR_FILENO, "bash: exit: %s: numeric argument \
				required\n", command->args[1]);
			return (ft_close_program(data, 2), 2);
		}
	}
	return (data->exit_code);
}

int	function_exit(t_command *command, t_shell *data)
{
	int	len;

	if (!ft_validate_command(command, "exit") || !command || !command->args)
		return (1);
	ft_printf(STDOUT_FILENO, "exit\n");
	len = ft_len_table(command->args);
	if (len > 2)
		return (exit_extra_args(command, data));
	else if (len == 2)
		return (exit_exact_args(command, data, len));
	return (printf ("default exit"), data->exit_code); // TODO: remove printf
}
