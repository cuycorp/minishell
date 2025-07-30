/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_retokenize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 14:30:33 by mcamaren          #+#    #+#             */
/*   Updated: 2025/07/30 16:32:16 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_append_tokens(t_token *token_list)
{
	char	*new_input;
	char	*appended;
	char	*temp;

	new_input = ft_strdup("");
	if (!new_input)
		return (NULL);
	while (token_list)
	{
		temp = new_input;
		if (token_list->next)
			appended = ft_strjoin(token_list->value, " ");
		else
			appended = ft_strdup(token_list->value);
		if (!appended)
			return (free(new_input), NULL);
		new_input = ft_strjoin(new_input, appended);
		free(temp);
		free(appended);
		if (!new_input)
			return (NULL);
		token_list = token_list->next;
	}
	return (new_input);
}

static char	*ft_create_new_input(t_shell *data)
{
	if (!data)
		return (NULL);
	return (ft_append_tokens(data->tokens_list));
}



bool	ft_retokenize(t_shell *data)
{
	char	*new_input;

	if (!data)
		return (false);
	new_input = ft_create_new_input(data);
	if(!new_input)
		return (false);
	free(data->input); // TODO: Questions: does the input really need to be free here?
	ft_free_tokens_list(&data->tokens_list);
	data->input = ft_strdup(new_input);
	if (data->input == NULL)
		return (false);
	ft_tokenizer(new_input, data);
	free(new_input);
	return (true);
}
