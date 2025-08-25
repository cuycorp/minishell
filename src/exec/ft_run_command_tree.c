/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run_command_tree.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 11:32:22 by jgossard          #+#    #+#             */
/*   Updated: 2025/08/25 14:17:24 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_run_command_tree(t_ast_node *root, t_shell *data)
{
	int	exit_code;

	if (!root || !data)
		return (EXIT_FAILURE);
	data->context = ft_create_exec_context(root);
	if (!data->context)
	{
		ft_printf(STDERR_FILENO,
			"minishell: data->context: constructor failed: %s\n",
			strerror(errno));
		return (EXIT_FAILURE);
	}
	if (!ft_process_heredocs(root, data))
	{
		exit_code = data->exit_code;
		ft_free_exec_context(data->context);
		data->context = NULL;
		return (exit_code);
	}
	ft_exec_node_recursive(root, data, data->context);
	ft_free_exec_context(data->context);
	data->context = NULL;
	if (data->has_raised_error)
		data->exit_code = 1;
	return (data->exit_code);
}

/*
//         PIPE
//       /      \
//     PIPE     cmd3
//    /    \
//  cmd1  cmd2 */

// cat infile | ls | wc -l
