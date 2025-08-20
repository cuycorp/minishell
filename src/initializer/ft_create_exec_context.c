/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_exec_context.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 15:07:42 by jgossard          #+#    #+#             */
/*   Updated: 2025/08/20 15:48:50 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_exec_context	*ft_create_exec_context(t_ast_node *root)
{
	t_exec_context	*context;

	if (!root)
		return (NULL);
	context = malloc(sizeof(t_exec_context));
	if (!context)
		return (NULL);
	context->input_fd = STDIN_FILENO;
	context->output_fd = STDOUT_FILENO;
	context->last_exit_code = 0;
	return (context);
}
