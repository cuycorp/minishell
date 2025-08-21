/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_append_remaining_arguments.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 13:46:31 by jgossard          #+#    #+#             */
/*   Updated: 2025/08/21 13:56:12 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	ft_set_command_name_from_args(t_command *command, bool *has_cmd)
{
	if (!command || !has_cmd)
		return (false);
	if (!*has_cmd && command->args && command->args[0])
	{
		command->name = ft_strdup(command->args[0]);
		if (!command->name)
			return (false);
		*has_cmd = true;
	}
	return (true);
}

bool	ft_append_remaining_arguments(t_command *command,
		t_token **tokens, bool *has_cmd)
{
	unsigned int	arg_count;
	char			*word;

	if (!command || !tokens || !*tokens)
		return (true);
	arg_count = 0;
	while (command->args && command->args[arg_count])
		arg_count++;
	while (*tokens && ft_is_argument_type((*tokens)->type)
		&& !ft_is_command_terminator((*tokens)->type))
	{
		word = ft_parse_command_word(tokens);
		if (!word)
			return (false);
		if (!ft_append_to_string_array(&command->args, &arg_count, word))
			return (free(word), false);
		free(word);
		if (!ft_set_command_name_from_args(command, has_cmd))
			return (false);
	}
	if (command->args)
		command->args[arg_count] = NULL;
	return (true);
}
