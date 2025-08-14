/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_evaluate_var_creation.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 14:18:22 by mcamaren          #+#    #+#             */
/*   Updated: 2025/07/23 21:44:56 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	ft_is_valid_var_name(char *var_declaration, int *j)
{
	if (!var_declaration)
		return (false);
	while (var_declaration[*j] && var_declaration[*j] != '=')
	{
		if (*j == 0 && !(ft_isalpha(var_declaration[*j])
				|| var_declaration[*j] == '_'))
			return (perror("not a valid identifier:"), ft_printf(STDERR_FILENO,
					" %s\n", var_declaration), false);
		else if (!(ft_isalnum(var_declaration[*j])
				|| var_declaration[*j] == '_'))
			return (perror("not a valid identifier:"), ft_printf(STDERR_FILENO,
					" %s\n", var_declaration), false);
		(*j)++;
	}
	return (true);
}

static char	**ft_append_str_to_table(char *new_str, char **table)
{
	int		i;
	char	**new_table;

	i = 0;
	if (!table || !new_str)
		return (NULL);
	new_table = ft_alloc_struct((ft_len_table(table) + 2) * sizeof(char *));
	if (!new_table)
		return (NULL);
	while (i < ft_len_table(table))
	{
		new_table[i] = ft_strdup(table[i]);
		if (!new_table[i])
			return (ft_free_char_tab(new_table), NULL);
		i++;
	}
	new_table[i] = ft_strdup(new_str);
	if (!new_table[i])
		return (ft_free_char_tab(new_table), NULL);
	new_table[i + 1] = NULL;
	ft_free_char_tab(table);
	return (new_table);
}

static bool	ft_add_vars_to_table(int to_env, char *var_definition,
		t_shell *data)
{
	if (!var_definition)
		return (false);
	if (to_env)
	{
		if (!ft_var_definition_exists(var_definition, data->ev))
			data->ev = ft_append_str_to_table(var_definition, data->ev);
		else if (!ft_replace_var_definition(var_definition, data->ev))
			return (false);
		if (!data->ev)
			return (false);
	}
	if (ft_var_definition_exists(var_definition, data->export))
	{
		if (to_env)
		{
			if (!ft_replace_var_definition(var_definition, data->export))
				return (false);
		}
	}
	else
		data->export = ft_append_str_to_table(var_definition, data->export);
	if (!data->export)
		return (false);
	return (true);
}

static char	*ft_create_var_definition(char *arguments, int *j, int *to_env)
{
	char	*var_definition;
	char	*var_name;

	if (!arguments)
		return (false);
	var_name = ft_substr(arguments, 0, *j);
	if (!var_name)
		return (NULL);
	if (arguments[*j] == '=')
	{
		*to_env = 1;
		var_definition = ft_strjoin(var_name, &arguments[*j]);
		if (!var_definition)
			return (free(var_name), NULL);
		return (free(var_name), var_definition);
	}
	else
		return (var_name);
}

bool	ft_evaluate_var_creation(t_command *command, t_shell *data)
{
	char	*var_definition;
	int		i;
	int		j;
	int		to_env;

	i = 1;
	j = 0;
	to_env = 0;
	while (command->args[i])
	{
		if (ft_is_valid_var_name(command->args[i], &j) == true)
		{
			var_definition = ft_create_var_definition(command->args[i], &j,
					&to_env);
			if (var_definition == NULL)
				return (false);
			if (ft_add_vars_to_table(to_env, var_definition, data) == false)
				return (free(var_definition), false);
			free(var_definition);
		}
		j = 0;
		to_env = 0;
		i++;
	}
	return (true);
}
