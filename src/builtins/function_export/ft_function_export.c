/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_function_export.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 19:39:21 by mcamaren          #+#    #+#             */
/*   Updated: 2025/07/23 15:55:12 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	function_export(t_command *command, t_shell *data)
{
	if (!command->name || !command->args || !data || !command->args[0])
		return (EXIT_FAILURE);
	if (ft_validate_command(command, "export") == false)
		return (EXIT_FAILURE);
	if (ft_len_table(command->args) == 1)
	{
		if (ft_strncmp(command->name, "export", ft_strlen(command->name)) == 0
			&& ft_strncmp(command->args[0], "export",
				ft_strlen(command->args[0])) == 0)
		{
			if (ft_print_export(data) == false)
				return (EXIT_FAILURE);
		}
		else
			return (EXIT_FAILURE);
	}
	else
	{
		if (ft_evaluate_var_creation(command, data) == false)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

/*
+ export with no arguments
	alone prints "export structure"
+ export with arguments
	valid var_name : [0-9][a-z][A-Z], starts with letter or underscore
		for unvalid,
			error message: bash: export: `1forb': not a valid identifier
	+ export create empty variable
	+ syntax to create variable name
		export varname
			-> creates var in export
		export varname=
			-> creates var in export and env:
				if unvalid content, creates empty string
+options provided -> send as error
export structure
	1. declare -x
	2. contains variables that have not finished declaring
*/

/*
1. export newz= -> create empty variable
2. export newz="$a"v ->crate empty variable, where "$a" does not exist
3.

*/
