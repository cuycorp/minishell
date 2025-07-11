/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_env_value.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 17:00:48 by jgossard          #+#    #+#             */
/*   Updated: 2025/07/07 17:01:22 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_split_env_value(char *key, char **envp)
{
	char	*env_value;
	char	**split_env_value;

	if (!key || !envp)
		return (NULL);
	env_value = ft_get_env_value(key, envp);
	if (!env_value)
		return (NULL);
	split_env_value = ft_split(env_value, ':');
	free(env_value);
	if (!split_env_value)
		return (NULL);
	return (split_env_value);
}
