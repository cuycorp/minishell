/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_shell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 09:28:04 by jgossard          #+#    #+#             */
/*   Updated: 2025/05/22 15:24:09 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_handle_shell(t_shell *data)
{
	while (1)
	{
		data->input = readline("Oh-My-Shell > ");
		if (!data->input)
			return (ft_close_program(data, EXIT_FAILURE));
		if (*data->input == '\0')
			continue;
		ft_handle_history(data->input);
		if (ft_strncmp(data->input, EXIT, ft_strlen(EXIT) + 1) == 0)
		{
			ft_putstr_fd(data->input, STDOUT_FILENO);
			break;
		}
		else
			ft_printf(STDOUT_FILENO, "%s\n", data->input);
	}
}
