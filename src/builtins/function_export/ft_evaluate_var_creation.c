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

static void	ft_init_evaluate_var_creation(int *i, int *j, int *to_env,
		bool *ret)
{
	*ret = true;
	*i = 1;
	*j = 0;
	*to_env = 0;
}

static void	ft_reset_evaluate_var_creation(int *i, int *j, int *to_env)
{
	if (!i)
		return ;
	(*i)++;
	*j = 0;
	*to_env = 0;
}

bool	ft_evaluate_var_creation(t_command *command, t_shell *data)
{
	char	*definition;
	int		i;
	int		j;
	int		to_env;
	bool	ret;

	if (!command || !data)
		return (false);
	ft_init_evaluate_var_creation(&i, &j, &to_env, &ret);
	while (command->args[i])
	{
		if (ft_is_valid_var_name(command->args[i], &j) == true)
		{
			definition = ft_set_var_definition(command->args[i], &j, &to_env);
			if (definition == NULL)
				return (false);
			if (ft_add_vars_to_table(to_env, definition, data) == false)
				return (free(definition), false);
			free(definition);
		}
		else
			ret = false;
		ft_reset_evaluate_var_creation(&i, &j, &to_env);
	}
	return (ret);
}
