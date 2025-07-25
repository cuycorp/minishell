/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_waitpid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamaren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 16:00:20 by mcamaren          #+#    #+#             */
/*   Updated: 2025/08/01 16:00:23 by mcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_waitpid(int pid, t_exec_context *context)
{
	if (!context)
		return (false);
	if (waitpid(pid, &context->last_exit_code, 0) != 1)
	{
		// TODO: add signal exit in the following if-statement
		if (WIFEXITED(context->last_exit_code))
		{
			ft_printf(STDERR_FILENO, "in WIFEXITED case\n");
			context->last_exit_code = WEXITSTATUS(context->last_exit_code);
		}
		else if (WIFSIGNALED(context->last_exit_code))
		{
			ft_printf(STDERR_FILENO, "in WIFSIGNALED case\n");
			context->last_exit_code = 128 + WTERMSIG(context->last_exit_code);
		}
		else
			context->last_exit_code = EXIT_FAILURE;
	}
	else
		return (false);
	return (true);
}
