/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_input.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 15:28:29 by jgossard          #+#    #+#             */
/*   Updated: 2025/08/21 16:04:52 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	ft_tokenize_and_expand(t_shell *data)
{
	if (!data)
		return (false);
	ft_tokenizer(data->input, data);
	if (data->tokens_list && data->tokens_list->type == TOKEN_END_OF_LINE)
		return (false);
	if (!ft_expansion_n_removal(data))
	{
		ft_printf(STDERR_FILENO,
			"minishell: error occurred during expansion\n");
		return (false);
	}
	return (true);
}

static bool	ft_parse_input_to_ast(t_shell *data)
{
	if (!data)
		return (false);
	if (data->tokens_list && data->tokens_list->type != TOKEN_END_OF_LINE)
	{
		data->ast_root = ft_parser(data->tokens_list);
		if (!data->ast_root)
		{
			ft_printf(STDERR_FILENO, "Error: ft_parser failed\n");
			return (false);
		}
	}
	return (true);
}

bool	ft_process_input(t_shell *data)
{
	if (!data)
		return (false);
	if (!ft_tokenize_and_expand(data))
	{
		ft_reset_shell(data);
		return (false);
	}
	if (!ft_parse_input_to_ast(data))
	{
		ft_reset_shell(data);
		return (false);
	}
	return (true);
}
