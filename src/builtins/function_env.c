/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamaren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:50:51 by mcamaren          #+#    #+#             */
/*   Updated: 2025/07/09 18:50:52 by mcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	function_env(t_command *command, t_shell *data)
{
	int	len_arg;

	if (!command || !data || !data->ev || !command->args)
		return (EXIT_FAILURE);
	len_arg = ft_len_table(command->args);
	if (len_arg != 1)
		return (EXIT_FAILURE);
	if (ft_strncmp(command->name, "env", ft_strlen(command->name)))
		return (EXIT_FAILURE);
	ft_print_table(data->ev);
	return (EXIT_SUCCESS);
}
