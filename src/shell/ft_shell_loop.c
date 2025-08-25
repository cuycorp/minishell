/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell_loop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 15:05:22 by jgossard          #+#    #+#             */
/*   Updated: 2025/08/21 16:04:47 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	ft_validate_input(t_shell *data)
{
	if (!data)
		return (true);
	if (!data->input || *data->input == '\0')
	{
		ft_reset_shell(data);
		return (true);
	}
	ft_handle_history(data->input);
	if (!ft_are_quotes_balanced(data->input))
	{
		ft_printf(STDERR_FILENO, "minishell: error: unbalanced quotes\n");
		ft_reset_shell(data);
		return (true);
	}
	return (false);
}


void	ft_shell_loop(t_shell *data)
{
	if (!data)
		return ;
	while (1)
	{
		data->prompt = ft_set_prompt(data);
		if (!data->prompt)
			return ;
		data->input = readline(data->prompt);
		ft_ctrl_d(data);
		if (ft_validate_input(data))
			continue ;
		if (!ft_process_input(data))
			continue ;
		if (data->ast_root)
			data->exit_code = ft_run_command_tree(data->ast_root, data);
		ft_reset_shell(data);
	}
}
