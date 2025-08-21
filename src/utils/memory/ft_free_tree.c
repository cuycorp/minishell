/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamaren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 16:03:44 by mcamaren          #+#    #+#             */
/*   Updated: 2025/08/21 16:03:47 by mcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_tree(t_shell *data)
{
	if (data && data->ast_root)
	{
		ft_close_heredocs_fd(data->ast_root);
		ft_free_ast_tree(&data->ast_root);
		data->ast_root = NULL;
		data->last_redirection = NULL;
	}
}
