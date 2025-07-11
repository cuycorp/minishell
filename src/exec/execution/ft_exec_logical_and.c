/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_logical_and.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 15:11:35 by jgossard          #+#    #+#             */
/*   Updated: 2025/07/25 18:47:13 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exec_logical_and(t_ast_node *node, t_shell *data,
		int input_fd, int *last_pid)
{
	int	result;

	if (!node || !data || !last_pid)
		return (EXIT_FAILURE);
	result = ft_execute_ast_tree(node->left, data, input_fd, last_pid);
	if (result == EXIT_SUCCESS)
		return (ft_execute_ast_tree(node->right, data, STDIN_FILENO, last_pid));
	if (input_fd != STDIN_FILENO)
		close(input_fd);
	return (result);
}
