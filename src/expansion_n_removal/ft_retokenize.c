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

char *ft_create_new_input(t_shell *data)
{
	t_token	*current;
	char	*new_input;
	char	*appended;
	char	*temp;

	new_input = ft_strdup("");
	current = data->tokens_list;
	while (current)
	{
		temp = new_input;
		if(current->next)
			appended = ft_strjoin(current->value, " ");
		else
			appended = ft_strdup(current->value);
		new_input = ft_strjoin(new_input, appended);
		free(temp);
		free(appended);
		current = current->next;
	}
	return (new_input);

}
void	ft_retokenize(t_shell *data)
{
	char	*new_input;

	new_input = ft_create_new_input(data);
	free(data->input);
	ft_free_tokens_list(&data->tokens_list);
	data->input = ft_strdup(new_input);
	ft_tokenizer(new_input, data);
	free(new_input);
}
