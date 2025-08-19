/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamaren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 14:42:02 by mcamaren          #+#    #+#             */
/*   Updated: 2025/07/11 14:42:04 by mcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**ft_fill_new_table(char *var_name, char **table, char **new_tab)
{
	int		i;
	int		j;
	char	*table_var_name;

	i = 0;
	j = 0;
	while (table[i])
	{
		table_var_name = ft_get_var_name(table[i]);
		if (!table_var_name)
			return (ft_free_char_tab(new_tab), NULL);
		if (!ft_is_same_var(var_name, table_var_name))
		{
			new_tab[j] = ft_strdup(table[i]);
			if (!new_tab[j])
				return (ft_free_char_tab(new_tab), free(table_var_name), NULL);
			j++;
		}
		free(table_var_name);
		i++;
	}
	new_tab[j] = NULL;
	return (new_tab);
}

static char	**ft_remove_var_of_table(char *var_name, char **table)
{
	char	**new_tab;

	new_tab = ft_alloc_struct(ft_len_table(table) * sizeof(char *));
	if (!new_tab)
		return (NULL);
	new_tab = ft_fill_new_table(var_name, table, new_tab);
	if (!new_tab)
		return (NULL);
	return (ft_free_char_tab(table), new_tab);
}

static bool	ft_var_name_exists(char *var_name, char **table)
{
	int		i;
	char	*table_var_name;

	i = 0;
	if (!var_name || !table)
		return (false);
	while (table[i])
	{
		table_var_name = ft_get_var_name(table[i]);
		if (!table_var_name)
			return (false);
		if (ft_strlen(table_var_name) == ft_strlen(var_name)
			&& ft_strncmp(table_var_name, var_name, ft_strlen(var_name)) == 0)
			return (free(table_var_name), true);
		free(table_var_name);
		i++;
	}
	return (false);
}

static bool	ft_unset_vars_from_table(char **args, char ***table)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (ft_var_name_exists(args[i], *table) && ft_strncmp("_", args[i], 2))
		{
			*table = ft_remove_var_of_table(args[i], *table);
			if (*table == NULL)
				return (false);
		}
		i++;
	}
	return (true);
}

bool	ft_unset_var(t_command *command, t_shell *data)
{
	if (!command->args || !command->args[1])
		return (false);
	if (!ft_unset_vars_from_table(command->args, &data->ev))
		return (false);
	if (!ft_unset_vars_from_table(command->args, &data->export))
		return (false);
	return (true);
}
