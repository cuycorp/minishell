/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace_var_definition.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamaren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 16:23:15 by mcamaren          #+#    #+#             */
/*   Updated: 2025/07/09 16:23:17 by mcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_var_name(char *var_definition)
{
	int		i;
	char	*var_name;

	i = 0;
	while (var_definition[i])
	{
		if (var_definition[i] == '=')
			break ;
		i++;
	}
	var_name = ft_substr(var_definition, 0, i);
	if (!var_name)
		return (NULL);
	return (var_name);
}

bool	ft_var_definition_exists(char *var_definition, char **table)
{
	int		i;
	char	*incoming_var_name;
	char	*table_var_name;

	i = 0;
	if (!var_definition || !table)
		return (false);
	incoming_var_name = ft_get_var_name(var_definition);
	if (!incoming_var_name)
		return (false);
	while (table[i])
	{
		table_var_name = ft_get_var_name(table[i]);
		if (!table_var_name)
			return (free(incoming_var_name), false);
		if (ft_strlen(table_var_name) == ft_strlen(incoming_var_name)
			&& ft_strncmp(table_var_name, incoming_var_name,
				ft_strlen(incoming_var_name)) == 0)
			return (free(incoming_var_name), free(table_var_name), true);
		free(table_var_name);
		i++;
	}
	return (free(incoming_var_name), false);
}

bool	ft_is_same_var(char *var_name1, char *var_name2)
{
	if (ft_strlen(var_name1) == ft_strlen(var_name2) && ft_strncmp(var_name1,
			var_name2, ft_strlen(var_name1)) == 0)
		return (true);
	return (false);
}

bool	ft_replace_var_definition(char *new_var_definition, char **table)
{
	int		i;
	char	*in_vname;
	char	*table_vname;

	i = 0;
	in_vname = ft_get_var_name(new_var_definition);
	if (!in_vname)
		return (false);
	while (table[i])
	{
		table_vname = ft_get_var_name(table[i]);
		if (!table_vname)
			return (free(in_vname), false);
		if (ft_is_same_var(in_vname, table_vname))
		{
			free(table[i]);
			table[i] = ft_strdup(new_var_definition);
			if (!table[i])
				return (false);
		}
		free(table_vname);
		i++;
	}
	return (free(in_vname), true);
}
