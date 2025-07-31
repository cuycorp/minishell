/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mark_pids_reaped.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 19:35:40 by jgossard          #+#    #+#             */
/*   Updated: 2025/07/31 19:36:04 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_mark_pids_reaped(t_exec_context *context)
{
	int	i = 0;

	if (!context || !context->pids)
		return;
	while (context->pids[i])
	{
		context->pids[i] = -1;
		i++;
	}
}
