/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_exec_context.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 15:07:42 by jgossard          #+#    #+#             */
/*   Updated: 2025/07/28 20:03:53 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_exec_context	*ft_create_exec_context(t_ast_node *root)
{
	t_exec_context *context;

	if (!root)
		return (NULL);
	context = malloc(sizeof(t_exec_context));
	if (!context)
		return (NULL);
	context->last_pid = -1;
	context->pid_count = 0;
	context->command_count = ft_count_cmd_nodes(root);
	if (context->command_count > 0)
	{
		context->pids = malloc(sizeof(pid_t) * context->command_count);
		if (!context->pids)
			return (NULL);
	}
	context->input_fd = STDIN_FILENO;
	context->output_fd = STDOUT_FILENO;
	context->needs_fork = false;
	context->is_last_command = false;
	return (context);
}
