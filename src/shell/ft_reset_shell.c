/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reset_shell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 23:32:50 by jgossard          #+#    #+#             */
/*   Updated: 2025/08/20 15:00:32 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_reset_context_struct(t_shell *data)
{
	if (data->context)
	{
		ft_free_exec_context(data->context);
		data->context = NULL;
	}
	if (data->wildcard)
	{
		ft_free_wildcard_context(data->wildcard);
		data->wildcard = NULL;
	}
}

void	ft_reset_shell(t_shell *data)
{
	if (!data)
		return ;
	if (data->input)
	{
		free(data->input);
		data->input = NULL;
	}
	if (data->prompt)
	{
		free(data->prompt);
		data->prompt = NULL;
	}
	if (data->tokens_list)
		ft_free_tokens_list(&data->tokens_list);
	if (data->ast_root)
	{
		ft_close_heredocs_fd(data->ast_root);
		ft_free_ast_tree(&data->ast_root);
		data->last_redirection = NULL;
	}
	ft_reset_context_struct(data);
	data->has_raised_error = false;
	if (data->last_redirection)
	{
		free(data->last_redirection);
		data->last_redirection = NULL;
	}
}
