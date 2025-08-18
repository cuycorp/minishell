/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run_command_tree.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 11:32:22 by jgossard          #+#    #+#             */
/*   Updated: 2025/08/18 16:59:25 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_run_command_tree(t_ast_node *root, t_shell *data)
{
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
		ft_free_exec_context(data->context);
		return (EXIT_FAILURE);
	}
	ft_exec_node_recursive(root, data, data->context);
	if (!ft_wait_all_pids(data->context))
		return (EXIT_FAILURE);
	ft_close_heredocs_fd(root);
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
