/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamaren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 13:59:06 by mcamaren          #+#    #+#             */
/*   Updated: 2025/07/22 13:59:08 by mcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_find_env_value(char *full_var, char **env)
{
	int		i;
	int		len;
	char	*expanded_value;

	len = ft_strlen(full_var);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], full_var, len) == 0)
		{
			expanded_value = ft_strdup(&env[i][len]);
			if (!expanded_value)
				return (NULL);
			return (expanded_value);
		}
		i++;
	}
	return (NULL);
}

char	*ft_expand_var(char *var_name, t_shell *data)
{
	char	*full_var;
	char	*expanded_value;

	if (!var_name || !data)
		return (NULL);
	full_var = ft_strjoin(var_name, "=");
	if (!full_var)
		return (NULL);
	expanded_value = ft_find_env_value(full_var, data->ev);
	if (!expanded_value)
		expanded_value = ft_strdup("");
	free(full_var);
	return (expanded_value);
}
