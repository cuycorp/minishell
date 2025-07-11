/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_in_tree_form.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:26:21 by mcamaren          #+#    #+#             */
/*   Updated: 2025/07/24 10:32:51 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	ft_print_ast_node(t_ast_node *node)
// {
// 	if (!node)
// 		return ;
// 	ft_printf(STDOUT_FILENO, "%s\n", node->value);
// }

// void	ft_print_in_tree_form(t_ast_node *node, int level)
// {
// 	int	ind_step;
// 	int	i;

// 	i = 0;
// 	ind_step = 4;
// 	if (!node)
// 		return ;
// 	ft_print_in_tree_form(node->right, level + 1);
// 	while (i < level * ind_step)
// 	{
// 		ft_printf(STDOUT_FILENO, " ");
// 		i++;
// 	}
// 	ft_printf(STDOUT_FILENO, "%s\n", node->value);
// 	ft_print_in_tree_form(node->left, level + 1);
// }



static void	print_redirection(t_redirection *redir)
{
	while (redir)
	{
		if (redir->type == REDIRECT_IN)
			ft_printf(STDERR_FILENO, "Redirect In: ");
		else if (redir->type == REDIRECT_OUT)
			ft_printf(STDERR_FILENO, "Redirect Out: ");
		else if (redir->type == APPEND_OUT)
			ft_printf(STDERR_FILENO, "Append Out: ");
		else if (redir->type == HEREDOC)
			ft_printf(STDERR_FILENO, "Heredoc: ");
		else
			ft_printf(STDERR_FILENO, "Unknown Redirection: ");
		ft_printf(STDERR_FILENO, "Target: %s\n", redir->target);
		redir = redir->next;
	}
}

static void	print_command(t_command *cmd)
{
	if (cmd)
	{
		ft_printf(STDERR_FILENO, "Command: %s\n", cmd->name);
		if (cmd->args)
		{
			ft_printf(STDERR_FILENO, "Args: ");
			for (int i = 0; cmd->args[i] != NULL; i++)
				ft_printf(STDERR_FILENO, "%s ", cmd->args[i]);
			ft_printf(STDERR_FILENO, "\n");
		}
		if (cmd->redirection)
			print_redirection(cmd->redirection);
	}
}

static void	print_ast_node(t_ast_node *node, int level)
{
	int	i;

	if (!node)
		return;
	// Indentation for readability
	i = 0;
	while (i < level)
	{
		ft_printf(STDERR_FILENO, "  ");
		i++;
	}

	// Print node type
	if (node->type == AST_PIPE)
		ft_printf(STDERR_FILENO, "AST_PIPE\n");
	else if (node->type == AST_SIMPLE_COMMAND)
		ft_printf(STDERR_FILENO, "AST_SIMPLE_COMMAND\n");
	else if (node->type == AST_REDIRECTION)
		ft_printf(STDERR_FILENO, "AST_REDIRECTION\n");
	else if (node->type == AST_LOGICAL_AND)
		ft_printf(STDERR_FILENO, "AST_LOGICAL_AND\n");
	else if (node->type == AST_LOGICAL_OR)
		ft_printf(STDERR_FILENO, "AST_LOGICAL_OR\n");
	else
		ft_printf(STDERR_FILENO, "Unknown Node Type\n");

	// Print command data
	if (node->command_data)
		print_command(node->command_data);

	// Print redirection data
	if (node->redirection_data)
		print_redirection(node->redirection_data);

	// Recursively print left and right children
	if (node->left)
	{
		ft_printf(STDERR_FILENO, "\nLeft Child:\n");
		print_ast_node(node->left, level + 1);
	}
	if (node->right)
	{
		ft_printf(STDERR_FILENO, "\nRight Child:\n");
		print_ast_node(node->right, level + 1);
	}
}

void	ft_print_ast_node(t_ast_node *root)
{
	if (!root)
	{
		ft_printf(STDERR_FILENO, "AST is empty\n");
		return;
	}
	ft_printf(STDERR_FILENO, "AST Tree:\n");
	print_ast_node(root, 0);
}
