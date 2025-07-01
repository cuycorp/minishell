/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_and_fill_command.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 11:42:41 by jgossard          #+#    #+#             */
/*   Updated: 2025/07/01 20:06:35 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	ft_add_argument_to_command(t_command *command, char *word, int *i,
		bool *has_command)
{
	if (!command || !word)
		return (false);
	if (!*has_command)
	{
		command->name = ft_strdup(word);
		if (!command->name)
			return (false);
		*has_command = true;
	}
	command->args[*i] = word;
	(*i)++;
	return (true);
}

static bool	ft_fill_command_from_tokens(t_command *cmd, t_token **tokens,
		int count, bool *has_cmd)
{
	char	*word;
	int		i;

	i = 0;
	while (*tokens && ft_is_argument_type((*tokens)->type)
		&& !ft_is_command_terminator((*tokens)->type) && i < count)
	{
		word = ft_parse_command_word(tokens);
		if (!word)
			return (false);
		if (!ft_add_argument_to_command(cmd, word, &i, has_cmd))
			return (free(word), false);
	}
	return (true);
}

t_command	*ft_create_and_fill_command(t_token **tokens, bool *has_command)
{
	t_command	*command;
	int			count;

	if (!tokens || !*tokens)
		return (NULL);
	count = ft_count_arguments(*tokens);
	if (count == 0)
		return (NULL);
	command = ft_create_command(count);
	if (!command)
		return (NULL);
	if (!ft_fill_command_from_tokens(command, tokens, count, has_command))
	{
		ft_free_command(command);
		*has_command = false;
		return (NULL);
	}
	return (command);
}
