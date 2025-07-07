/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamaren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 14:06:59 by mcamaren          #+#    #+#             */
/*   Updated: 2025/07/09 14:07:01 by mcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	process_export_var(t_shell *data, char *export_var)
{
	int		j;
	char	*search;
	char	*var_name;
	char	*expand_var;

	j = 0;
	search = ft_strjoin("$", export_var);
	if (!search)
		return (false);
	var_name = ft_locate_var(search, &j);
	if (!var_name)
		return (free(search), false);
	expand_var = ft_expand_var(var_name, data);
	if (!expand_var)
	{
		free(search);
		free(var_name);
		return (false);
	}
	ft_printf(STDOUT_FILENO, "declare -x %s=\"%s\"\n", var_name, expand_var);
	free(search);
	free(var_name);
	free(expand_var);
	return (true);
}

bool	ft_print_export(t_shell *data)
{
	int		i;

	i = 0;
	if (!data || !data->export)
		return (false);
	while (data->export[i])
	{
		if (!process_export_var(data, data->export[i]))
			return (false);
		i++;
	}
	return (true);
}
