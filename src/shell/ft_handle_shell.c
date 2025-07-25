/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_shell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 09:28:04 by jgossard          #+#    #+#             */
/*   Updated: 2025/07/31 20:08:08 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_close_heredocs_fd(t_ast_node *node)
{
	t_redirection	*redirection;

	if (!node)
		return ;
	if (node->type == AST_SIMPLE_COMMAND && node->command_data)
	{
		redirection = node->command_data->redirection;
		while (redirection)
		{
			if (redirection->type == HEREDOC && redirection->heredoc_fd != -1)
			{
				close(redirection->heredoc_fd);
				redirection->heredoc_fd = -1;
			}
			redirection = redirection->next;
		}
	}
	ft_close_heredocs_fd(node->left);
	ft_close_heredocs_fd(node->right);
}

static void	ft_reset_shell(t_shell *data)
{
	if (!data)
		return ;
	if (data->input)
	{
		free(data->input);
		data->input = NULL;
	}
	if (data->tokens_list)
		ft_free_tokens_list(&data->tokens_list);
	if (data->ast_root)
	{
		ft_close_heredocs_fd(data->ast_root);
		ft_free_ast_tree(&data->ast_root);
	}
}

static char	*ft_set_prompt(t_shell *data)
{
	char	*prompt;
	int		i;
	char	*pwd;
	char	*equal_sign;

	if (!data)
		return (NULL);
	i = 0;
	while (data->ev[i] && ft_strncmp(data->ev[i], "PWD", ft_strlen("PWD")) != 0)
		i++;
	equal_sign = ft_strchr(data->ev[i], '=');
	if (!equal_sign)
		return (ft_strdup(" Oh-My-Shell > "));
	pwd = equal_sign + 1;
	prompt = ft_strjoin(pwd, " Oh-My-Shell > ");
	return (prompt);
}

void	ft_handle_shell(t_shell *data)
{
	char	*prompt;

	// int		last_pid;
	// int		exit_code;
	prompt = ft_set_prompt(data);
	if (!prompt)
		return ;
	while (1)
	{
		data->input = readline(prompt);
		// History
		ft_handle_history(data->input);
		if (ft_interactive_ctrl_c(data))
			continue;
		ft_ctrl_d(data, prompt);
		if (*data->input == '\0')
		{
			ft_reset_shell(data);
			continue ;
		}
		// History
		ft_handle_history(data->input);
		// Quote checking
		if (!ft_are_quotes_balanced(data->input))
		{
			ft_printf(STDERR_FILENO, "minishell: error: unbalanced quotes\n");
			ft_reset_shell(data);
			continue ;
		}
		// EXIT
		if (ft_strncmp(data->input, EXIT, ft_strlen(EXIT) + 1) == 0)
		{
			ft_putstr_fd(data->input, STDOUT_FILENO);
			break ;
		}
		// TOKENIZATION
		ft_tokenizer(data->input, data);
		// Expansion and Quotes Removal
		if (!ft_expansion_n_removal(data))
		{
			ft_printf(STDERR_FILENO,
				"minishell: error occured during expansion\n");
			ft_reset_shell(data);
			continue ;
		}
		ft_print_tokens_list(data); // TODO: remove this line
		// Parsing
		if (data->tokens_list && data->tokens_list->type != TOKEN_END_OF_LINE)
		{
			data->ast_root = ft_parser(data->tokens_list);
			if (!data->ast_root)
			{
				ft_printf(STDERR_FILENO, "Error: ft_parser failed\n");
				ft_reset_shell(data);
				continue ;
			}
		}
		// EXECUTION
		if (data->ast_root)
		{
			data->exit_code = ft_run_command_tree(data->ast_root, data);
			ft_printf(STDOUT_FILENO, "exit code = %d\n", data->exit_code);
		}
		ft_reset_shell(data);
	}
	// TODO: add clear_history????
	rl_clear_history(); // TODO: not sure
	free(prompt);
}
