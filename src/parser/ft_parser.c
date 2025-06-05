/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamaren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 11:41:53 by mcamaren          #+#    #+#             */
/*   Updated: 2025/06/05 11:41:56 by mcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_parser(t_token *token_list, t_shell *data);
bool	ft_parse_shell(t_token *token_list, t_shell *data);
bool	ft_parse_command_line(t_token **token_list, t_shell *data);
bool	ft_parse_grouped_pipeline(t_token **token_list, t_shell *data);
bool	ft_parse_pipeline(t_token **token_list, t_shell *data);
bool	ft_parse_simple_command(t_token **token_list, t_shell *data);
bool	ft_parse_redirection(t_token *token_list, t_shell *data);
bool	ft_parse_arguments(t_token *token_list, t_shell *data);
bool	ft_parse_word(t_token *token_list, t_shell *data);
bool	ft_parse_quoted_string(t_token *token_list, t_shell *data);
bool	ft_parse_single_quoted(t_token *token_list, t_shell *data);
bool	ft_parse_double_quoted_string(t_token *token_list, t_shell *data);
bool	ft_parse_double_quoted_char(t_token *token_list, t_shell *data);
bool	ft_parse_env_variable(t_token *token_list, t_shell *data);
bool	ft_parse_env_name(t_token *token_list, t_shell *data);

bool	ft_parse_simple_command(t_token **token_list, t_shell *data)
{
	(void)data;
	ft_printf(1, "in ft_parse_simple_command, curent = %s \n",
		(*token_list)->value);
	if ((*token_list)->type == TOKEN_WORD)
	{
		*token_list = (*token_list)->next;
		return (ft_printf(1, "ft_parse_simple_command = true\n"), true);
	}
	else
		return (perror("Error: is not of type TOKEN_WORD\n"), false);
}

bool	ft_parse_pipeline(t_token **token_list, t_shell *data)
{
	if (!ft_parse_simple_command(token_list, data))
		return (perror("Error: ft_parse_simple_command failed\n"), false);
	while ((*token_list))
	{
		ft_printf(1, "current %s \n", (*token_list)->value);
		if ((*token_list)->type == TOKEN_PIPE)
		{
			*token_list = (*token_list)->next;
			if (!ft_parse_simple_command(token_list, data))
				return (perror("Error: ft_parse_simple_command failed\n"),
					false);
			*token_list = (*token_list)->next;
		}
		else
		{
			return (perror("Error: is not type of TOKEN_PIPE"), false);
		}
	}
	return (true);
}

bool	ft_parse_command_line(t_token **token_list, t_shell *data)
{
	if (!ft_parse_pipeline(token_list, data))
		return (false);
	return (true);
}

bool	ft_parser(t_token *token_list, t_shell *data)
{
	t_token	*current;

	current = token_list;
	if (!ft_parse_command_line(&current, data))
		return (false);
	return (true);
}
