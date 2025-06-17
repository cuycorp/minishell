/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_shell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 09:28:04 by jgossard          #+#    #+#             */
/*   Updated: 2025/07/01 21:02:33 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_reset_shell(t_shell *data)
{
	if (!data)
		return ;
	if (data->input)
		free(data->input);
	if (data->tokens_list)
		ft_free_tokens_list(&data->tokens_list);
	if (data->ast_root)
		ft_free_ast_tree(&data->ast_root);
}

static char	*ft_set_prompt(t_shell *data)
{
	char	*prompt;
	int		i;
	char	*pwd;
	char	*equal_sign;

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

	prompt = ft_set_prompt(data);
	if (!prompt)
		return ;
	while (1)
	{
		data->input = readline(prompt);
		if (!data->input)
			return (free(prompt), ft_close_program(data, EXIT_FAILURE));
		if (*data->input == '\0')
			continue ;
		// EXIT
		if (ft_strncmp(data->input, EXIT, ft_strlen(EXIT) + 1) == 0)
		{
			ft_putstr_fd(data->input, STDOUT_FILENO);
			break ;
		}
		else
			ft_printf(STDOUT_FILENO, "%s\n", data->input);
		// TOKENIZATION
		ft_tokenizer(data->input, data);
		// VAR_EXPANSION
		ft_var_expansion(&data->tokens_list, data);
		ft_retokenize(data);
		ft_quote_removal(&data->tokens_list);
		// Parsing
		if (data->tokens_list && data->tokens_list->type != TOKEN_END_OF_LINE)
		{
			data->ast_root = ft_parser(data->tokens_list);
			if (!data->ast_root)
				ft_printf(STDERR_FILENO, "Error: ft_parser failed\n");
			else
				ft_printf(STDIN_FILENO, "Success: ft_parser succeeded\n");
		}
		ft_handle_history(data->input);
		ft_reset_shell(data);
	}
	free(prompt);
}

/*

void	ft_handle_shell(t_shell *data)
{
	int	i;

	i = 0;
	while (1)
	{
		data->input = readline(prompt);
		if (!data->input)
			return (free(prompt), ft_close_program(data, EXIT_FAILURE));
		if (*data->input == '\0')
			continue ;
		// EXIT
		ft_tokenizer(data->input, data);
		ft_handle_history(data->input);
		ft_var_expansion(&data->tokens_list, data);
		ft_retokenize(data);
		ft_quote_removal(&data->tokens_list);
		if (ft_strncmp(data->input, EXIT, ft_strlen(EXIT) + 1) == 0)
		{
			ft_putstr_fd(data->input, STDOUT_FILENO);
			break ;
		}
		else
			ft_printf(STDOUT_FILENO, "%s\n", data->input);
		// TOKENIZATION
		ft_tokenizer(data->input, data);
		// Parsing
		if (data->tokens_list && data->tokens_list->type != TOKEN_END_OF_LINE)
		{
			data->ast_root = ft_parser(data->tokens_list);
			if (!data->ast_root)
				ft_printf(STDERR_FILENO, "Error: ft_parser failed\n");
			else
				ft_printf(STDIN_FILENO, "Success: ft_parser succeeded\n");
		}
		ft_handle_history(data->input);
		// else
		// ft_printf(STDOUT_FILENO, "%s\n", data->input);
		ft_reset_shell(data);
	}
	free(prompt);
}

*/

/*
VAR = "AAA" -> AAA

echo $VAR
type = TOKEN_EXPANSION
value = $VAR

expsansion of $
type = TOKEN_EXPANSION
value = AAA


echo "$VAR"
type = TOKEN__DOUBLE_QUOTED_WORD
value = "$VAR"

expansion of $
type = TOKEN__DOUBLE_QUOTED_WORD
value = "AAA"


*/
