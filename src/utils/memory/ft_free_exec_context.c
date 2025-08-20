/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_exec_context.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 17:13:50 by jgossard          #+#    #+#             */
/*   Updated: 2025/08/20 15:48:41 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_exec_context(t_exec_context *context)
{
	if (!context)
		return ;
	ft_safe_close_and_reset_fd(&context->input_fd);
	ft_safe_close_and_reset_fd(&context->output_fd);
	free(context);
}
