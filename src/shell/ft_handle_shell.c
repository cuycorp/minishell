/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_shell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 09:28:04 by jgossard          #+#    #+#             */
/*   Updated: 2025/08/04 23:35:02 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_set_prompt(t_shell *data)
{
	char	*prompt;
	int		i;
	char	*pwd;
	char	*equal_sign;

	if (!data)
		return (NULL);
	i = 0;
	while (data->ev[i] && ft_strncmp(data->ev[i], "PWD=",
			ft_strlen("PWD=")) != 0)
		i++;
	if (!data->ev[i])
		return (ft_strdup(PROMPT));
	equal_sign = ft_strchr(data->ev[i], '=');
	if (!equal_sign)
		return (ft_strdup(PROMPT));
	pwd = equal_sign + 1;
	prompt = ft_strjoin(pwd, PROMPT);
	return (prompt);
}

void	ft_handle_shell(t_shell *data)
{
	if (!data)
		return ;
	ft_ctrl_c();
	while (1)
	{
		data->prompt = ft_set_prompt(data);
		if (!data->prompt)
			break ;
		data->input = readline(data->prompt);
		if (!data->input)
			break ;
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
			ft_reset_shell(data);
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
		// ft_print_tokens_list(data); // TODO: remove this line
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
}
