/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_in_tree_form.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamaren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:26:21 by mcamaren          #+#    #+#             */
/*   Updated: 2025/06/24 11:26:23 by mcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_ast_node(t_ast_node *node)
{
	if (!node)
		return ;
	ft_printf(STDOUT_FILENO, "%s\n", node->value);
}

void	ft_print_in_tree_form(t_ast_node *node, int level)
{
	int	ind_step;
	int	i;

	i = 0;
	ind_step = 4;
	if (!node)
		return ;
	ft_print_in_tree_form(node->right, level + 1);
	while (i < level * ind_step)
	{
		ft_printf(STDOUT_FILENO, " ");
		i++;
	}
	ft_printf(STDOUT_FILENO, "%s\n", node->value);
	ft_print_in_tree_form(node->left, level + 1);
}
