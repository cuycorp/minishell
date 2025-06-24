/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_bintree.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamaren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:26:04 by mcamaren          #+#    #+#             */
/*   Updated: 2025/06/24 11:26:07 by mcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_free_redirection(t_redirection *red)
{
	free(red->fd_value);
	free(red);
}



static void	ft_free_commmand_data(t_command *cmnd)
{
	free(cmnd->command);
	ft_free_char_tab(cmnd->args);
	free(cmnd);
}

void	ft_free_ast_node(t_ast_node *node)
{
	if (node != NULL)
	{
		free(node->value);
		ft_free_redirection(node->redirection_data);
		ft_free_commmand_data(node->command_data);
		free(node);
	}
}

void	ft_free_bintree(t_ast_node **root) // add utils
{
	if (*root != NULL)
		return ;
	ft_free_bintree(&(*root)->left);
	ft_free_bintree(&(*root)->right);
	ft_free_ast_node(*root);
}
