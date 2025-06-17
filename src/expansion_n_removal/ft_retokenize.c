/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_retokenize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamaren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 14:30:33 by mcamaren          #+#    #+#             */
/*   Updated: 2025/07/01 14:30:36 by mcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	ft_retokenize(t_shell *data)
{
	char	*new_input;
	char	*tmp;
	char	*join_tmp;
	t_token	*current;

	new_input = ft_strdup("");
	current = data->tokens_list;
	while (current)
	{
		if (current->next)
		{
			join_tmp = ft_strjoin(current->value, " ");
			tmp = ft_strjoin(new_input, join_tmp);
			free(join_tmp);
		}
		else
			tmp = ft_strjoin(new_input, current->value);
		free(new_input);
		new_input = tmp;
		current = current->next;
	}
	free(data->input);
	ft_free_tokens_list(&data->tokens_list);
	data->input = ft_strdup(new_input);
	free(new_input);
	ft_tokenizer(data->input, data);
}
