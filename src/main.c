/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 14:08:57 by jgossard          #+#    #+#             */
/*   Updated: 2025/07/01 21:03:24 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell		*data;
	t_command	*builtin;

	(void)argv;
	// (void)argc;
	data = ft_init_shell(envp);
	if (!data)
		return (EXIT_FAILURE);
	builtin = ft_alloc_struct(sizeof(t_command));
	if (!builtin)
		return (1);
	builtin->args = ft_split("", ' ');
	if (!builtin->args)
		return (ft_clear_memory(data), ft_free_command(builtin), 1);
	builtin->name = ft_strdup("cd");
	if (!builtin->name)
		return (ft_free_command(builtin), ft_clear_memory(data), 1);
	ft_validate_args(argc, data);
	// ft_handle_shell(data);
	if (function_cd(&data, builtin))
		return (ft_free_command(builtin), ft_clear_memory(data), 1);
	ft_free_command(builtin);
	ft_clear_memory(data);
	return (EXIT_SUCCESS);
}
