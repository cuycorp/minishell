/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 14:08:57 by jgossard          #+#    #+#             */
/*   Updated: 2025/05/30 15:33:44 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell	*data;

	(void)argv;
	(void)argc;
	data = ft_init_shell(envp);
	if (!data)
		return (EXIT_FAILURE);
	ft_validate_args(argc, data);
	ft_handle_shell(data);
	ft_clear_memory(data);
	return (EXIT_SUCCESS);
}


/* int	main(void)
{
	t_ast_node	*node_a;
	t_ast_node	*node_b;
	t_ast_node	*operator;

	node_a = ft_create_ast_node(AST_SIMPLE_COMMAND);
	node_a->left = 0;
	node_a->right = 0;
	node_a->value = ft_strdup("echo");
	node_a->type = AST_SIMPLE_COMMAND;
	node_a->redirection_data->fd_value = ft_strdup("monkyes");
	node_a->redirection_data->type = REDIRECT_IN;
	node_a->command_data->args = ft_split("miau-guau", '-');
	node_a->command_data->command = ft_strdup("cats");

	node_b = ft_create_ast_node(AST_SIMPLE_COMMAND);
	node_b->left = 0;
	node_b->right = 0;
	node_b->value = ft_strdup("cat");
	node_b->type = AST_SIMPLE_COMMAND;
	node_b->redirection_data->fd_value = ft_strdup("monkyes");
	node_b->redirection_data->type = REDIRECT_IN;
	node_b->command_data->args = ft_split("miau-guau", '-');
	node_b->command_data->command = ft_strdup("cats");


	operator = ft_create_ast_node(AST_SIMPLE_COMMAND);
	operator->left = node_b;
	operator->right = node_a;
	operator->value = ft_strdup("pipe");
	operator->type = AST_SIMPLE_COMMAND;
	operator->redirection_data->fd_value = ft_strdup("monkyes");
	operator->redirection_data->type = REDIRECT_IN;
	operator->command_data->args = ft_split("miau-guau", '-');
	operator->command_data->command = ft_strdup("cats");

	ft_print_ast_node(operator);
	ft_print_in_tree_form(operator, 0);
	ft_free_bintree(&operator);
	ft_free_ast_node(operator);
	ft_free_ast_node(node_a);
	ft_free_ast_node(node_b);
} */

/* static void	test_builtin(t_shell **data)
{
	t_command	command;
	t_command	command2;
	char		*PATH;

	PATH = "src";
	command.args = ft_split(PATH, ' ');
	command.command = "cd";
	command.redirection = NULL;
	command.next = NULL;
	command2.args = ft_split("-n Hello mcamaren", ' ');
	command2.command = "echo";
	command2.redirection = NULL;
	command2.next = NULL;
	printf("Inside cd\n");
	function_cd(data, command);
	printf("Inside pwd\n");
	function_pwd(*data);
	printf("Inside echo\n");
	function_echo(command2);
}
 */
