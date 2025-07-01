/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clear_memory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 14:57:54 by jgossard          #+#    #+#             */
/*   Updated: 2025/07/01 19:20:28 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_clear_memory(t_shell *data)
{
	if (!data)
		return ;
	if (data->input)
		free(data->input);
	if (data->tokens_list)
		ft_free_tokens_list(&data->tokens_list);
	if (data->ast_root)
		ft_free_ast_tree(&data->ast_root);
	if (data->ev)
		ft_free_char_tab(data->ev);
	free(data);
}
