/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clear_memory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 14:57:54 by jgossard          #+#    #+#             */
/*   Updated: 2025/08/20 19:23:20 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_free_export(t_shell *data)
{
	if (data && data->export)
	{
		ft_free_char_tab(data->export);
		data->export = NULL;
	}
}

static void	ft_free_tokens(t_shell *data)
{
	if (data && data->tokens_list)
		ft_free_tokens_list(&data->tokens_list);
}

static void	ft_free_tree(t_shell *data)
{
	if (data && data->ast_root)
	{
		ft_close_heredocs_fd(data->ast_root);
		ft_free_ast_tree(&data->ast_root);
		data->ast_root = NULL;
		data->last_redirection = NULL;
	}
}

static void	ft_free_context(t_shell *data)
{
	if (data && data->context)
	{
		ft_free_exec_context(data->context);
		data->context = NULL;
	}
}

void	ft_clear_memory(t_shell *data)
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
	if (data->ev)
	{
		ft_free_char_tab(data->ev);
		data->ev = NULL;
	}
	ft_free_export(data);
	ft_free_tokens(data);
	ft_free_tree(data);
	ft_free_context(data);
	if (data->wildcard)
		ft_free_wildcard_context(data->wildcard);
	if (data->last_redirection)
	{
		free(data->last_redirection);
		data->last_redirection = NULL;
	}
	if (data->error_message)
	{
		free(data->error_message);
		data->error_message = NULL;
	}
	free(data);
}
