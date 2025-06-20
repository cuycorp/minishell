/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_ast_node.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 09:55:24 by jgossard          #+#    #+#             */
/*   Updated: 2025/06/20 17:59:07 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_free_ast_node(t_ast_node *node);\
void		ft_print_ast_node(t_ast_node *node, void (*applyf)(void *));
void		ft_free_bintree(t_ast_node **root);

t_ast_node	*ft_create_ast_node(t_ast_node_type type)
{
	t_ast_node	*node;

	node = ft_alloc_struct(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = type;
	return (node);
}


void	pointer_print(void *str)
{
	printf("%s\n", (char *)str);
}

void	ft_print_ast_node(t_ast_node *node, void (*applyf)(void *))
{
	if (!node)
		return ;
	btree_apply_infix(node->left, applyf);
	applyf(node->value);
	btree_apply_infix(node->right, applyf);
}

void	ft_free_redirection(t_redirection *red)
{
	free(red->fd_value);
	free(red);
}

void	free_matrix(char **str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	ft_free_commmand_data(t_command *cmnd)
{
	free(cmnd->command);
	free_matrix(cmnd->args);
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
	t_list *buff;

	if (*root != NULL)
		return ;
	ft_free_bintree(&(*root)->left);
	ft_free_bintree(&(*root)->right);
	ft_free_ast_node(*root);
}


