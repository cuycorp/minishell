/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ctrl_d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamaren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 17:46:09 by mcamaren          #+#    #+#             */
/*   Updated: 2025/07/24 17:46:12 by mcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_ctrl_d(t_shell *data, char *prompt)
{
	if (!data->input)
	{
		write(STDOUT_FILENO, "exit\n", 5);
		free(prompt);
		ft_close_program(data, data->exit_code);
	}
}
