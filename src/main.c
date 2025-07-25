/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 14:08:57 by jgossard          #+#    #+#             */
/*   Updated: 2025/07/28 19:44:06 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_sigflag	g_signal = 0;

int	main(int argc, char **argv, char **envp)
{
	t_shell	*data;

	(void)argv;
	// (void)argc;
	data = ft_init_shell(envp);
	if (!data)
		return (EXIT_FAILURE);
	ft_validate_args(argc, data);
	ft_ctrl_c();
	ft_ctrl_slash();
	ft_handle_shell(data);
	ft_clear_memory(data);
	return (EXIT_SUCCESS);
}
