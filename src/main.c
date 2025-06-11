/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 14:08:57 by jgossard          #+#    #+#             */
/*   Updated: 2025/05/30 15:33:44 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	test_builtin(t_shell **data)
{
	t_command	command;
	char		*PATH;

	PATH = "src";
	command.args = ft_split(PATH, ' ');
	command.command = "cd";
	command.redirection = NULL;
	command.next = NULL;
	function_cd(data, command);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*data;

	(void)argv;
	(void)argc;
	data = ft_init_shell(envp);
	test_builtin(&data); //test builtins
	if (!data)
		return (EXIT_FAILURE);
	ft_validate_args(argc, data);
	ft_handle_shell(data);
	ft_clear_memory(data);
	return (EXIT_SUCCESS);
}
