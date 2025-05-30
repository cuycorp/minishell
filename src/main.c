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

int main(int argc, char **argv, char **envp)
{
	(void)argv;
	(void)envp;
	t_shell	*data;

	data = ft_init_shell();
	if (!data)
		return (EXIT_FAILURE);
	ft_validate_args(argc, data);
	ft_handle_shell(data);
	ft_clear_memory(data);
	return (EXIT_SUCCESS);
}
