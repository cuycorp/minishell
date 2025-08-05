/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ctrl_d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamaren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:26:46 by mcamaren          #+#    #+#             */
/*   Updated: 2025/08/05 18:26:48 by mcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_ctrl_d(t_shell *data)
{
	if (!data->input)
	{
		write(STDOUT_FILENO, "exit\n", 5);
		ft_close_program(data, data->exit_code);
	}
}
